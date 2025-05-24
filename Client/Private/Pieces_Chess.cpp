#include "Pieces_Chess.h"

CPieces_Chess::CPieces_Chess(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLandObject { pGraphic_Device }
{
}

CPieces_Chess::CPieces_Chess(const CPieces_Chess& Prototype)
	: CLandObject{ Prototype }
{
}

HRESULT CPieces_Chess::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPieces_Chess::Initialize(void* pArg)
{
	if (nullptr != pArg)
	{
		if (FAILED(__super::Initialize(pArg)))
			return E_FAIL;
	}

	return S_OK;
}

void CPieces_Chess::Priority_Update(_float fTimeDelta)
{
}

void CPieces_Chess::Update(_float fTimeDelta)
{
}

void CPieces_Chess::Late_Update(_float fTimeDelta)
{
}

HRESULT CPieces_Chess::Render()
{
	return S_OK;
}

void CPieces_Chess::SetUp_OnChessBoard(CTransform* pTransformCom)
{
	_float3     vWorldPos = pTransformCom->Get_State(STATE::POSITION);

	_float3     vLocalPos{};
	D3DXVec3TransformCoord(&vLocalPos, &vWorldPos, m_pLandTransform->Get_WorldMatrix_Inverse());

	vLocalPos = dynamic_cast<CVIBuffer_Board*>(m_pLandVIBuffer)->Compute_XYZ(vLocalPos);

	D3DXVec3TransformCoord(&vWorldPos, &vLocalPos, m_pLandTransform->Get_WorldMatrix());

	pTransformCom->Set_State(STATE::POSITION, vWorldPos);
}

void CPieces_Chess::Free()
{
	__super::Free();
}
