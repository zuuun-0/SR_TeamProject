#include "Level_Logo.h"

#include "BackGround.h"
#include "GameInstance.h"
#include "Level_Loading.h"

CLevel_Logo::CLevel_Logo(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel{ pGraphic_Device }
{}

HRESULT CLevel_Logo::Initialize()
{

	/* 현재 레벨을 구성해주기 위한 객체들을 생성한다. */
	if(FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;
	if(FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround_SERVER"))))
		return E_FAIL;
	return S_OK;
}

void CLevel_Logo::Update(_float fTimeDelta)
{
	if(GetKeyState(VK_RETURN) & 0x8000)
	{
		if(FAILED(m_pGameInstance->Open_Level(static_cast<_uint>(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_GAMEPLAY))))
			return;
	}

	return;
}

HRESULT CLevel_Logo::Render()
{
	SetWindowText(g_hWnd, TEXT("로고레벨입니다."));

	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_BackGround(const _wstring& strLayerTag)
{
	if(FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_LOGO), strLayerTag,
													  ENUM_CLASS(LEVEL::LEVEL_LOGO), TEXT("Prototype_GameObject_BackGround"))))
		return E_FAIL;
	//g_pClientPlayer = static_cast<CBackGround*>(m_pGameInstance->Get_Object(ENUM_CLASS(LEVEL::LEVEL_LOGO), strLayerTag));
	//g_pClientPlayer->SetClinetPlayer();
	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_BackGround_SERVER(const _wstring& strLayerTag)
{
	if(FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_LOGO), strLayerTag,
													  ENUM_CLASS(LEVEL::LEVEL_LOGO), TEXT("Prototype_GameObject_BackGround"))))
		return E_FAIL;
	//g_pServerPlayer = static_cast<CBackGround*>(m_pGameInstance->Get_Object(ENUM_CLASS(LEVEL::LEVEL_LOGO), strLayerTag));
	return S_OK;
}


CLevel_Logo* CLevel_Logo::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_Logo* pInstance = new CLevel_Logo(pGraphic_Device);

	if(FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed to Created : CLevel_Logo"));
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CLevel_Logo::Free()
{
	__super::Free();



}
