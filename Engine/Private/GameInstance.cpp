#include "GameInstance.h"

#include "Graphic_Device.h"
#include "Level_Manager.h"
#include "Object_Manager.h"
#include "Prototype_Manager.h"
#include "Renderer.h"
#include "Timer_Manager.h"

IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
	: m_pInput_Manager { CInput_Manager::GetInstance() }
	, m_pCollision_Manager { CCollision_Manager::GetInstance() }
{
	Safe_AddRef(m_pCollision_Manager);
	Safe_AddRef(m_pInput_Manager);
}

#pragma region ENGINE

HRESULT CGameInstance::Initialize_Engine(const ENGINE_DESC& EngineDesc, LPDIRECT3DDEVICE9* ppOut)
{
	m_pGraphic_Device = CGraphic_Device::Create(EngineDesc.hWnd, EngineDesc.eWinMode, EngineDesc.iWinSizeX, EngineDesc.iWinSizeY, ppOut);
	if(nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pLevel_Manager = CLevel_Manager::Create();
	if(nullptr == m_pLevel_Manager)
		return E_FAIL;

	m_pPrototype_Manager = CPrototype_Manager::Create(EngineDesc.iNumLevels);
	if(nullptr == m_pPrototype_Manager)
		return E_FAIL;

	m_pObject_Manager = CObject_Manager::Create(EngineDesc.iNumLevels);
	if(nullptr == m_pObject_Manager)
		return E_FAIL;

	m_pRenderer = CRenderer::Create(*ppOut);
	if(nullptr == m_pRenderer)
		return E_FAIL;

	m_pTimer_Manager = CTimer_Manager::Create();
	if(nullptr == m_pTimer_Manager)
		return E_FAIL;

	if (FAILED(m_pCollision_Manager->Initialize(m_pGraphic_Device->GetDevice())))
		return E_FAIL;


	return S_OK;
}

void CGameInstance::Update_Engine(_float fTimeDelta)
{
	/* 내 게임내에서 반복적인 갱신이 필요한 객체들이 있다라면 갱신을 여기에서 모아서 수행하낟. */

	m_pObject_Manager->Priority_Update(fTimeDelta);
	m_pObject_Manager->Update(fTimeDelta);
	m_pObject_Manager->Late_Update(fTimeDelta);

	m_pInput_Manager->Input_Update();

	m_pLevel_Manager->Update(fTimeDelta);
}

HRESULT CGameInstance::Clear_Resources(_uint iClearLevelID)
{
	/* 기존레벨용 자원들을 날린다. */
	m_pPrototype_Manager->Clear(iClearLevelID);

	m_pObject_Manager->Clear(iClearLevelID);

	return S_OK;
}

#pragma endregion

#pragma region GRAPHIC_DEVICE

void CGameInstance::Render_Begin(D3DXCOLOR Color)
{
	if(nullptr != m_pGraphic_Device)
		m_pGraphic_Device->Render_Begin(Color);
}

HRESULT CGameInstance::Draw()
{
	if(nullptr == m_pLevel_Manager ||
	   nullptr == m_pRenderer)
		return E_FAIL;

	m_pRenderer->Draw();

	if(FAILED(m_pLevel_Manager->Render()))
		return E_FAIL;

	return S_OK;
}

void CGameInstance::Render_End(HWND hWnd)
{
	if(nullptr != m_pGraphic_Device)
		m_pGraphic_Device->Render_End(hWnd);
}

LPDIRECT3DDEVICE9 CGameInstance::GetDevice()
{
	return m_pGraphic_Device->GetDevice();
}

#pragma endregion

#pragma region LEVEL_MANAGER

HRESULT CGameInstance::Open_Level(_uint iLevelID, CLevel* pNewLevel)
{
	if(nullptr == m_pLevel_Manager)
		return E_FAIL;

	return m_pLevel_Manager->Open_Level(iLevelID, pNewLevel);
}

_uint CGameInstance::Get_Current_LevelID()
{
	if(nullptr == m_pLevel_Manager)
		return 0;

	return m_pLevel_Manager->Get_Current_LevelID();
}

#pragma endregion

#pragma region PROTOTYPE_MANAGER

HRESULT CGameInstance::Add_Prototype(_uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, CBase* pPrototype)
{
 	if(nullptr == m_pPrototype_Manager)
		return E_FAIL;

	return m_pPrototype_Manager->Add_Prototype(iPrototypeLevelIndex, strPrototypeTag, pPrototype);
}

CBase* CGameInstance::Clone_Prototype(PROTOTYPE ePrototype, _uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, void* pArg)
{
	return m_pPrototype_Manager->Clone_Prototype(ePrototype, iPrototypeLevelIndex, strPrototypeTag, pArg);
}

#pragma endregion

#pragma region OBJECT_MANAGER

HRESULT CGameInstance::Add_GameObject_ToLayer(_uint iLayerLevelIndex, const _wstring& strLayerTag, _uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, void* pArg)
{
	if(nullptr == m_pObject_Manager)
		return E_FAIL;

	return m_pObject_Manager->Add_GameObject_ToLayer(iLayerLevelIndex, strLayerTag, iPrototypeLevelIndex, strPrototypeTag, pArg);
}

CComponent* CGameInstance::Get_Position(_uint iLayerLevelIndex, const _wstring& strLayerTag)
{
	if(nullptr == m_pObject_Manager)
		return nullptr;

	return m_pObject_Manager->Get_Position(iLayerLevelIndex, strLayerTag);
}

CGameObject* CGameInstance::Get_Object(_uint iLayerLevelIndex, const _wstring& strLayerTag)
{
	if(nullptr == m_pObject_Manager)
		return nullptr;

	return m_pObject_Manager->Get_Object(iLayerLevelIndex, strLayerTag);
}

CComponent* CGameInstance::Find_Component(_uint iLayerLevelIndex, const _wstring& strLayerTag, const _wstring& strComponentTag, _uint iIndex)
{
	if (nullptr == m_pObject_Manager)
		return nullptr;

	return m_pObject_Manager->Get_Component(iLayerLevelIndex, strLayerTag, strComponentTag, iIndex);
}

#pragma endregion

#pragma region RENDERER

HRESULT CGameInstance::Add_RenderGroup(RENDERGROUP eRenderGroup, CGameObject* pRenderObject)
{
	if(nullptr == m_pRenderer)
		return E_FAIL;

	return m_pRenderer->Add_RenderGroup(eRenderGroup, pRenderObject);
}

#pragma endregion

#pragma region TIMER_MANAGER

_float CGameInstance::Get_TimeDelta(const _wstring& strTimerTag)
{
	return m_pTimer_Manager->Get_TimeDelta(strTimerTag);
}

HRESULT CGameInstance::Add_Timer(const _wstring& strTimerTag)
{
	if(nullptr == m_pTimer_Manager)
		return E_FAIL;

	return m_pTimer_Manager->Add_Timer(strTimerTag);
}

void CGameInstance::Compute_TimeDelta(const _wstring& strTimerTag)
{
	if(nullptr == m_pTimer_Manager)
		return;

	return m_pTimer_Manager->Compute_TimeDelta(strTimerTag);
}

#pragma endregion

void CGameInstance::Release_Engine()
{
	Release();

	Safe_Release(m_pCollision_Manager);

	m_pCollision_Manager->Release_Collision();

	Safe_Release(m_pInput_Manager);

	m_pInput_Manager->Release_Input();

	Safe_Release(m_pTimer_Manager);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pObject_Manager);
	Safe_Release(m_pPrototype_Manager);
	Safe_Release(m_pLevel_Manager);
	Safe_Release(m_pGraphic_Device);
}

void CGameInstance::Free()
{
	__super::Free();


}
