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
	PIECE_DESC* PawnDesc = static_cast<PIECE_DESC*>(pArg);

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(STATE::POSITION, PawnDesc->vPosition);

	return S_OK;
}

void CBD_Pawn::Priority_Update(_float fTimeDelta)
{
	_float3 vWorldPos = m_pTransformCom->Get_State(STATE::POSITION);

	_float fPosX = m_pTransformCom->Get_State(STATE::POSITION).x;
	_float fPosY = m_pTransformCom->Get_State(STATE::POSITION).y;
	_float fPosZ = m_pTransformCom->Get_State(STATE::POSITION).z;

	if (m_pInput_Manager->Key_Down('W') && fPosZ < 7)
		m_pTransformCom->Chess_Up();

	if (m_pInput_Manager->Key_Down('A') && fPosX > 1)
		m_pTransformCom->Chess_Left();

	if (m_pInput_Manager->Key_Down('S') && fPosZ > 1)
		m_pTransformCom->Chess_Down();

	if (m_pInput_Manager->Key_Down('D') && fPosX < 7)
		m_pTransformCom->Chess_Right();
}

void CBD_Pawn::Update(_float fTimeDelta)
{
	SetUp_OnChessBoard(m_pTransformCom);
}

void CBD_Pawn::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_NONBLEND, this);
}

HRESULT CBD_Pawn::Render()
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

HRESULT CBD_Pawn::Ready_Components()
{
	CTransform::TRANSFORM_DESC TransformDesc{};

	TransformDesc.fSpeedPerSec = 8.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(30.f);

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom), &TransformDesc)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Pawn"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
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
