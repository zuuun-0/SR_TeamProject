#include "Pieces_Chess.h"

CPieces_Chess::CPieces_Chess(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject { pGraphic_Device }
{
}

CPieces_Chess::CPieces_Chess(const CPieces_Chess& Prototype)
	: CGameObject { Prototype }
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

void CPieces_Chess::Free()
{
	__super::Free();
}
