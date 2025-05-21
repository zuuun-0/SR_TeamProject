#include "Client_defines.h"
#include "GameInstance.h"
#include "Player.h"

USING(Client)

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject{ pGraphic_Device }
{}

CPlayer::CPlayer(const CPlayer& Prototype)
	: CGameObject{ Prototype }
{}

HRESULT CPlayer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlayer::Initialize(void* pArg)
{
	if(FAILED(Ready_Components()))
		return E_FAIL;

	return S_OK;
}

void CPlayer::Priority_Update(_float fTimeDelta)
{}

void CPlayer::Update(_float fTimeDelta)
{
	//if(!m_bClientPlayer) return;
	bool isMoved = false;

	//if(GetKeyState(VK_UP) & GetKeyState(VK_SHIFT) & 0x8000)
	//	m_pTransformCom->Go_Straight(fTimeDelta);
	//if(GetKeyState('W') & 0x8000)
	//	m_pTransformCom->Go_Straight(fTimeDelta);

	//else if(GetKeyState(VK_UP) & 0x8000)
	//{
	//	m_pTransformCom->Turn(_float3(1.f, 0.f, 0.f), fTimeDelta);
	//}

	//if(GetKeyState(VK_DOWN) & GetKeyState(VK_SHIFT) & 0x8000)
	//	m_pTransformCom->Go_Backward(fTimeDelta);

	//if(GetKeyState('S') & 0x8000)
		//m_pTransformCom->Go_Backward(fTimeDelta);
	//else if(GetKeyState(VK_DOWN) & 0x8000)
	//{
	//	m_pTransformCom->Turn(_float3(1.f, 0.f, 0.f), fTimeDelta * -2.f);
	//}

	//if(GetKeyState('A') & 0x8000)
	//{
	//	m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta * -5.f);
	//}
	//
	//if(GetKeyState('D') & 0x8000)
	//{
	//	m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta * 5.f);
	//}
}

void CPlayer::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_PRIORITY, this);
}

HRESULT CPlayer::Render()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pTransformCom->Bind_Matrix();

	if(FAILED(m_pTextureCom->Bind_Texture()))
		return E_FAIL;

	/* 그리기위해 이용할 자원과 설정들을 장치에 바인딩한다. */
	m_pVIBufferCom->Bind_Buffers();

	m_pVIBufferCom->Render();

	return S_OK;
}

void CPlayer::SetClinetPlayer()
{
	m_bClientPlayer = true;
}

HRESULT CPlayer::Ready_Components()
{
	if(FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Cube"),
									 TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	if(FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_Component_Texture_Player"),
									 TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	CTransform::TRANSFORM_DESC TransformDesc{};

	TransformDesc.fSpeedPerSec = 8.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(30.f);

	if(FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
									 TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom), &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CPlayer* pInstance = new CPlayer(pGraphic_Device);

	if(FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CPlayer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CPlayer::Clone(void* pArg)
{
	CPlayer* pInstance = new CPlayer(*this);

	if(FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CPlayer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPlayer::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
