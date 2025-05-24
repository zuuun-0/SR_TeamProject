#include "BD_Queen.h"

CBD_Queen::CBD_Queen(LPDIRECT3DDEVICE9 DEVICE)
	: CPieces_Chess(DEVICE)
{}

CBD_Queen::CBD_Queen(const CBD_Queen& OTHDER)
	: CPieces_Chess(OTHDER)
{}

HRESULT CBD_Queen::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CBD_Queen::Initialize(void* pArg)
{
	if(FAILED(Ready_Components()))
		return E_FAIL;

	return S_OK;
}
void CBD_Queen::Priority_Update(_float fTimeDelta)
{

}

void CBD_Queen::Update(_float fTimeDelta)
{
	SetUp_OnChessBoard(m_pTransformCom);
}

void CBD_Queen::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_NONBLEND, this);
}

HRESULT CBD_Queen::Render()
{
	m_pTransformCom->Scaling(0.15f, 0.15f, 0.15f);

	m_pTransformCom->Bind_Matrix();

	/* 그리기위해 이용할 자원과 설정들을 장치에 바인딩한다. */
	m_pVIBufferCom->Bind_Buffers();

	SetUp_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();

	return S_OK;
}

void CBD_Queen::SetClinetPlayer()
{
	m_bClientPlayer = true;
}


HRESULT CBD_Queen::Ready_Components()
{
	CTransform::TRANSFORM_DESC TransformDesc{};

	TransformDesc.fSpeedPerSec = 8.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(30.f);

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom), &TransformDesc)))
		return E_FAIL;

	if(FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Queen"),
									 TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	return S_OK;
}

void CBD_Queen::SetUp_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CBD_Queen::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

CBD_Queen* CBD_Queen::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBD_Queen* pInstance = new CBD_Queen(pGraphic_Device);

	if(FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CBD_Queen"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CBD_Queen::Clone(void* pArg)
{
	auto* newObj = new CBD_Queen(*this);
	if(FAILED(newObj->Initialize(pArg)))
	{
		assert(false);
		Safe_Release(newObj);
	}
	return newObj;
}

void CBD_Queen::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
