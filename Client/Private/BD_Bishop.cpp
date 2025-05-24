#include "BD_Bishop.h"


CBD_Bishop::CBD_Bishop(LPDIRECT3DDEVICE9 DEVICE)
	: CPieces_Chess(DEVICE)
{}

CBD_Bishop::CBD_Bishop(const CBD_Bishop& OTHDER)
	: CPieces_Chess(OTHDER)
{}

HRESULT CBD_Bishop::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CBD_Bishop::Initialize(void* pArg)
{
	if(FAILED(Ready_Components()))
		return E_FAIL;

	auto* tf = static_cast<CTransform*>(Get_Component(TEXT("Com_Transform")));
	tf->Set_State(STATE::POSITION, _float3(5.f, 0.f, 0.f));


	return S_OK;
}
void CBD_Bishop::Priority_Update(_float fTimeDelta)
{}


void CBD_Bishop::Update(_float fTimeDelta)
{}


void CBD_Bishop::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_NONBLEND, this);
}

HRESULT CBD_Bishop::Render()
{
	m_pTransformCom->Bind_Matrix();

	m_pVIBufferCom->Bind_Buffers();

	SetUp_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();

	return S_OK;
}

HRESULT CBD_Bishop::Ready_Components()
{
	if(FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Bishop"),
									 TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	//if(FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_Component_Texture_Queen"),
	//								 TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
	//	return E_FAIL;

	CTransform::TRANSFORM_DESC TransformDesc{};

	TransformDesc.fSpeedPerSec = 8.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(30.f);

	if(FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
									 TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom), &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

void CBD_Bishop::SetUp_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CBD_Bishop::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

CBD_Bishop* CBD_Bishop::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBD_Bishop* pInstance = new CBD_Bishop(pGraphic_Device);

	if(FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : Bishop"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CBD_Bishop::Clone(void* pArg)
{
	auto* newObj = new CBD_Bishop(*this);
	if(FAILED(newObj->Initialize(pArg)))
	{
		assert(false);
		Safe_Release(newObj);
	}
	return newObj;
}

void CBD_Bishop::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
