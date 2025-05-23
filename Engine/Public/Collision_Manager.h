#pragma once

#include "RayCast.h"

BEGIN(Engine)

class ENGINE_DLL CCollision_Manager : public CBase
{
	DECLARE_SINGLETON(CCollision_Manager)

private:
	CCollision_Manager();
	virtual ~CCollision_Manager() = default;

public:
	HRESULT Initialize(LPDIRECT3DDEVICE9 pGraphic_Device);


#pragma region RAY_CASTING

public:
	// 마우스 위치(스크린 좌표)를 받아 Ray 생성
	void ScreenPosToRay(_int iMouseX, _int iMouseY, D3DXVECTOR3& outvRayOrigin, D3DXVECTOR3& outvRayDir);

	// Ray와 AABB 교차 판정
	_bool RayIntersectsAABB(D3DXVECTOR3& rayOrigin, D3DXVECTOR3& rayDir, BOUNDINGBOX& box, float* outDist = nullptr);

	// Ray와 삼각형 교차 판정
	_bool RayIntersectsTriangle(D3DXVECTOR3& rayOrigin, D3DXVECTOR3& rayDir, TRIANGLE& tri, float* outDist = nullptr);

#pragma endregion

private:
	CRayCast* m_pRayCast = { nullptr };

public:
	void Release_Collision();
	virtual void Free() override;
};

END