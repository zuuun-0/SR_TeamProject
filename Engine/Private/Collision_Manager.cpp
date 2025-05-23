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

void CCollision_Manager::ScreenPosToRay(_int iMouseX, _int iMouseY, D3DXVECTOR3& outvRayOrigin, D3DXVECTOR3& outvRayDir)
{
	if (nullptr == m_pRayCast)
		return;

	m_pRayCast->ScreenPosToRay(iMouseX, iMouseY, outvRayOrigin, outvRayDir);
}

_bool CCollision_Manager::RayIntersectsAABB(D3DXVECTOR3& rayOrigin, D3DXVECTOR3& rayDir, BOUNDINGBOX& box, float* outDist)
{
	return m_pRayCast->RayIntersectsAABB(rayOrigin, rayDir, box, outDist);
}

_bool CCollision_Manager::RayIntersectsTriangle(D3DXVECTOR3& rayOrigin, D3DXVECTOR3& rayDir, TRIANGLE& tri, float* outDist)
{
	return m_pRayCast->RayIntersectsTriangle(rayOrigin, rayDir, tri, outDist);
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
