#include "Collision_Manager.h"

IMPLEMENT_SINGLETON(CCollision_Manager)

CCollision_Manager::CCollision_Manager()
{
}

HRESULT CCollision_Manager::Initialize(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	m_pRayCast = CRayCast::Create(pGraphic_Device);
	if (nullptr == m_pRayCast)
		return E_FAIL;

	return S_OK;
}

void CCollision_Manager::Release_Collision()
{
	Release();

	Safe_Release(m_pRayCast);
}

void CCollision_Manager::Free()
{
	__super::Free();
}
