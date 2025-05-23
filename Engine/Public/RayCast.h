#pragma once

BEGIN(Engine)

class CRayCast final : public CBase 
{
private:
    CRayCast(LPDIRECT3DDEVICE9 pGraphic_Device);
    virtual ~CRayCast() = default;

public:
    // 마우스 위치(스크린 좌표)를 받아 Ray 생성
    void ScreenPosToRay(_int iMouseX, _int iMouseY, D3DXVECTOR3& outvRayOrigin, D3DXVECTOR3& outvRayDir);

    // Ray와 AABB 교차 판정
    _bool RayIntersectsAABB(D3DXVECTOR3& rayOrigin, D3DXVECTOR3& rayDir, BOUNDINGBOX& box, float* outDist = nullptr);

    // Ray와 삼각형 교차 판정
    _bool RayIntersectsTriangle(D3DXVECTOR3& rayOrigin, D3DXVECTOR3& rayDir, TRIANGLE& tri, float* outDist = nullptr);

private:
    LPDIRECT3DDEVICE9 m_pGraphic_Device = { nullptr };

public:
    static CRayCast* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
    virtual void Free() override;
};

END