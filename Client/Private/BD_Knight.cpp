#include "BD_Knight.h"

#include "GameInstance.h"

CBD_Knight::CBD_Knight(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CPieces_Chess{ pGraphic_Device }
{
}

CBD_Knight::CBD_Knight(const CBD_Knight& Prototype)
	: CPieces_Chess{ Prototype }
{
}

HRESULT CBD_Knight::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CBD_Knight::Initialize(void* pArg)
{
	PIECE_DESC* pDesc = static_cast<PIECE_DESC*>(pArg);

	// m_iData = pDesc->iData;

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	//m_pTransformCom->Scaling(0.5f, 0.5f, 0.5f);

	return S_OK;
}

void CBD_Knight::Priority_Update(_float fTimeDelta)
{
}

void CBD_Knight::Update(_float fTimeDelta)
{
}

void CBD_Knight::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_PRIORITY, this);
}

HRESULT CBD_Knight::Render()
{
	m_pTransformCom->Bind_Matrix();

	// if (FAILED(m_pTextureCom->Bind_Texture()))
	// 	return E_FAIL;

	/* 그리기위해 이용할 자원과 설정들을 장치에 바인딩한다. */
	m_pVIBufferCom->Bind_Buffers();

	SetUp_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();

	return S_OK;
}

HRESULT CBD_Knight::Ready_Components()
{
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Knight"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	/*if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_Component_Texture_Player"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;*/

	CTransform::TRANSFORM_DESC TransformDesc{};

	TransformDesc.fSpeedPerSec = 8.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(30.f);

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom), &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

void CBD_Knight::SetUp_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CBD_Knight::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

CBD_Knight* CBD_Knight::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBD_Knight* pInstance = new CBD_Knight(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CBD_Knight"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CBD_Knight::Clone(void* pArg)
{
	CBD_Knight* pInstance = new CBD_Knight(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CBD_Knight"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBD_Knight::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
