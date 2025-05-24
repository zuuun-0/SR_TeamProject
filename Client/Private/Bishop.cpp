#include "Bishop.h"


CBishop::CBishop(LPDIRECT3DDEVICE9 DEVICE)
	: CPieces_FPS(DEVICE)
{}

CBishop::CBishop(const CBishop& OTHDER)
	: CPieces_FPS(OTHDER)
{}

HRESULT CBishop::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CBishop::Initialize(void* pArg)
{
	if(FAILED(Ready_Components()))
		return E_FAIL;

	auto* tf = static_cast<CTransform*>(Get_Component(TEXT("Com_Transform")));
	tf->Set_State(STATE::POSITION, _float3(5.f, 0.f, 0.f));


	return S_OK;
}
void CBishop::Priority_Update(_float fTimeDelta)
{}


void CBishop::Update(_float fTimeDelta)
{}


void CBishop::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_NONBLEND, this);
}

HRESULT CBishop::Render()
{
	m_pTransformCom->Bind_Matrix();

	m_pVIBufferCom->Bind_Buffers();

	SetUp_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();

	return S_OK;
}

HRESULT CBishop::Ready_Components()
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

void CBishop::SetUp_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CBishop::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

CBishop* CBishop::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBishop* pInstance = new CBishop(pGraphic_Device);

	if(FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : Bishop"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CBishop::Clone(void* pArg)
{
	auto* newObj = new CBishop(*this);
	if(FAILED(newObj->Initialize(pArg)))
	{
		assert(false);
		Safe_Release(newObj);
	}
	return newObj;
}

void CBishop::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
