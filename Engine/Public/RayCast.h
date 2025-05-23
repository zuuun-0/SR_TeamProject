#pragma once

BEGIN(Engine)

class CRayCast final : public CBase 
{
private:
    CRayCast(LPDIRECT3DDEVICE9 pGraphic_Device);
    virtual ~CRayCast() = default;

public:
    // ���콺 ��ġ(��ũ�� ��ǥ)�� �޾� Ray ����
    void ScreenPosToRay(_int iMouseX, _int iMouseY, D3DXVECTOR3& outvRayOrigin, D3DXVECTOR3& outvRayDir);

    // Ray�� AABB ���� ����
    _bool RayIntersectsAABB(D3DXVECTOR3& rayOrigin, D3DXVECTOR3& rayDir, BOUNDINGBOX& box, float* outDist = nullptr);

    // Ray�� �ﰢ�� ���� ����
    _bool RayIntersectsTriangle(D3DXVECTOR3& rayOrigin, D3DXVECTOR3& rayDir, TRIANGLE& tri, float* outDist = nullptr);

private:
    LPDIRECT3DDEVICE9 m_pGraphic_Device = { nullptr };

public:
    static CRayCast* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
    virtual void Free() override;
};

END