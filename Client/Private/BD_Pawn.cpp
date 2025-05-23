#include "BD_Pawn.h"

#include "GameInstance.h"

CBD_Pawn::CBD_Pawn(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CPieces_Chess{ pGraphic_Device }
{
}

CBD_Pawn::CBD_Pawn(const CBD_Pawn& Prototype)
	: CPieces_Chess{ Prototype }
{
}

HRESULT CBD_Pawn::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CBD_Pawn::Initialize(void* pArg)
{
	PIECE_DESC* pDesc = static_cast<PIECE_DESC*>(pArg);

	// m_iData = pDesc->iData;

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	return S_OK;
}

void CBD_Pawn::Priority_Update(_float fTimeDelta)
{
}

void CBD_Pawn::Update(_float fTimeDelta)
{
}

void CBD_Pawn::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_PRIORITY, this);
}

HRESULT CBD_Pawn::Render()
{
	m_pTransformCom->Bind_Matrix();

	// if (FAILED(m_pTextureCom->Bind_Texture()))
	// 	return E_FAIL;

	/* �׸������� �̿��� �ڿ��� �������� ��ġ�� ���ε��Ѵ�. */
	m_pVIBufferCom->Bind_Buffers();

	SetUp_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();

	return S_OK;
}

HRESULT CBD_Pawn::Ready_Components()
{
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Pawn"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	//if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Player"),
	//	TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
	//	return E_FAIL;

	CTransform::TRANSFORM_DESC TransformDesc{};

	TransformDesc.fSpeedPerSec = 8.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(30.f);

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom), &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

void CBD_Pawn::SetUp_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CBD_Pawn::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

CBD_Pawn* CBD_Pawn::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBD_Pawn* pInstance = new CBD_Pawn(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CBD_Pawn"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CBD_Pawn::Clone(void* pArg)
{
	CBD_Pawn* pInstance = new CBD_Pawn(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CBD_Pawn"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBD_Pawn::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
