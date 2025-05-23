#include "Pieces_FPS.h"

CPieces_FPS::CPieces_FPS(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLandObject { pGraphic_Device }
{
}

CPieces_FPS::CPieces_FPS(const CPieces_FPS& Prototype)
	: CLandObject { Prototype }
{
}

HRESULT CPieces_FPS::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPieces_FPS::Initialize(void* pArg)
{
	if (nullptr != pArg)
	{
		if (FAILED(__super::Initialize(pArg)))
			return E_FAIL;
	}

	return S_OK;
}

void CPieces_FPS::Priority_Update(_float fTimeDelta)
{
}

void CPieces_FPS::Update(_float fTimeDelta)
{
}

void CPieces_FPS::Late_Update(_float fTimeDelta)
{
}

HRESULT CPieces_FPS::Render()
{
	return S_OK;
}

void CPieces_FPS::Free()
{
	__super::Free();
}
