#include "Rook.h"

#include "GameInstance.h"

CRook::CRook(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject{ pGraphic_Device }
{
}

CRook::CRook(const CRook& Prototype)
	: CGameObject{ Prototype }
{
}

HRESULT CRook::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRook::Initialize(void* pArg)
{
	if (FAILED(Ready_Components()))
		return E_FAIL;

	return S_OK;
}

void CRook::Priority_Update(_float fTimeDelta)
{
}

void CRook::Update(_float fTimeDelta)
{
	//m_pTransformCom->Go_Straight(fTimeDelta);
}

void CRook::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_PRIORITY, this);
}

HRESULT CRook::Render()
{
	m_pTransformCom->Bind_Matrix();

	if (FAILED(m_pTextureCom->Bind_Texture()))
		return E_FAIL;

	/* 그리기위해 이용할 자원과 설정들을 장치에 바인딩한다. */
	m_pVIBufferCom->Bind_Buffers();

	SetUp_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();

	return S_OK;
}

HRESULT CRook::Ready_Components()
{
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Rook"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_Component_Texture_Player"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	CTransform::TRANSFORM_DESC TransformDesc{};

	TransformDesc.fSpeedPerSec = 8.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(30.f);

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom), &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

void CRook::SetUp_RenderState()
{
}

void CRook::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

CRook* CRook::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CRook* pInstance = new CRook(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CRook"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CRook::Clone(void* pArg)
{
	CRook* pInstance = new CRook(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CRook"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRook::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
