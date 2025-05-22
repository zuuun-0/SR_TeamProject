#include "Pawn.h"

#include "GameInstance.h"

CPawn::CPawn(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject{ pGraphic_Device }
{
}

CPawn::CPawn(const CPawn& Prototype)
	: CGameObject{ Prototype }
{
}

HRESULT CPawn::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPawn::Initialize(void* pArg)
{
	if (FAILED(Ready_Components()))
		return E_FAIL;

	return S_OK;
}

void CPawn::Priority_Update(_float fTimeDelta)
{
}

void CPawn::Update(_float fTimeDelta)
{
	if (m_pInput_Manager->Key_Pressing(VK_UP))
		m_pTransformCom->Go_Straight(fTimeDelta);

	if (m_pInput_Manager->Key_Pressing(VK_LEFT))
		m_pTransformCom->Turn(m_pTransformCom->Get_State(STATE::UP), fTimeDelta * -1.f);

	if (m_pInput_Manager->Key_Pressing(VK_DOWN))
		m_pTransformCom->Go_Backward(fTimeDelta);

	if (m_pInput_Manager->Key_Pressing(VK_RIGHT))
		m_pTransformCom->Turn(m_pTransformCom->Get_State(STATE::UP), fTimeDelta);
}

void CPawn::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_PRIORITY, this);
}

HRESULT CPawn::Render()
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

HRESULT CPawn::Ready_Components()
{
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Pawn"),
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

void CPawn::SetUp_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CPawn::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

CPawn* CPawn::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CPawn* pInstance = new CPawn(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CPawn"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CPawn::Clone(void* pArg)
{
	CPawn* pInstance = new CPawn(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CPawn"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPawn::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
