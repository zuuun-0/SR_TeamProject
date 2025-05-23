#include "RayCast.h"

CRayCast::CRayCast(LPDIRECT3DDEVICE9 pGrahpic_Device)
    : m_pGraphic_Device { pGrahpic_Device }
{
    Safe_AddRef(m_pGraphic_Device);
}

// 1. 마우스 스크린 좌표 → 3D 월드 Ray로 변환
void CRayCast::ScreenPosToRay(_int iMouseX, _int iMouseY, D3DXVECTOR3& outvRayOrigin, D3DXVECTOR3& outvRayDir)
{
    D3DVIEWPORT9 Viewport;
    m_pGraphic_Device->GetViewport(&Viewport);

    D3DXMATRIX matProj{}, matView{}, matWorld{};
    m_pGraphic_Device->GetTransform(D3DTS_PROJECTION, &matProj);
    m_pGraphic_Device->GetTransform(D3DTS_VIEW, &matView);
    D3DXMatrixIdentity(&matWorld);

    // 스크린 좌표를 NDC(-1~1)로 변환
    _float fPx = ((2.0f * iMouseX) / Viewport.Width - 1.0f);
    _float fPy = (1.0f - (2.0f * iMouseY) / Viewport.Height);

    // Near/Far 평면 좌표
    D3DXVECTOR3 vNear(fPx, fPy, 0.0f);
    D3DXVECTOR3 vFar(fPx, fPy, 1.0f);

    // 역투영
    _float3 vNearMouse = { (_float)iMouseX, (_float)iMouseY, 0.0f };
    _float3 vFarMouse = { (_float)iMouseX, (_float)iMouseY, 1.0f };


    D3DXVec3Unproject(&vNear, &vNearMouse, &Viewport, &matProj, &matView, &matWorld);
    D3DXVec3Unproject(&vFar, &vFarMouse, &Viewport, &matProj, &matView, &matWorld);

    outvRayOrigin = vNear;
    outvRayDir = vFar - vNear;
    D3DXVec3Normalize(&outvRayDir, &outvRayDir);
}

// 2. Ray vs. AABB (Axis-Aligned Bounding Box)
_bool CRayCast::RayIntersectsAABB(D3DXVECTOR3& vRayOrigin, D3DXVECTOR3& vRayDir, BOUNDINGBOX& Box, float* pOutDist)
{
    _float fMin = (Box.vMin.x - vRayOrigin.x) / vRayDir.x;
    _float fMax = (Box.vMax.x - vRayOrigin.x) / vRayDir.x;
    if (fMin > fMax) swap(fMin, fMax);

    _float fYmin = (Box.vMin.y - vRayOrigin.y) / vRayDir.y;
    _float fYmax = (Box.vMax.y - vRayOrigin.y) / vRayDir.y;
    if (fYmin > fYmax) swap(fYmin, fYmax);

    if ((fMin > fYmax) || (fYmin > fMax))
        return false;

    if (fYmin > fMin)
        fMin = fYmin;
    if (fYmax < fMax)
        fMax = fYmax;

    _float tzmin = (Box.vMin.z - vRayOrigin.z) / vRayDir.z;
    _float tzmax = (Box.vMax.z - vRayOrigin.z) / vRayDir.z;
    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((fMin > tzmax) || (tzmin > fMax))
        return false;

    if (tzmin > fMin)
        fMin = tzmin;
    if (tzmax < fMax)
        fMax = tzmax;

    if (fMax < 0)
        return false;

    if (pOutDist)
        *pOutDist = fMin;

    return true;
}

// 3. Ray vs. Triangle (Möller–Trumbore Algorithm)
_bool CRayCast::RayIntersectsTriangle(D3DXVECTOR3& vRayOrigin, D3DXVECTOR3& vRayDir, TRIANGLE& tri, float* outDist)
{
    const _float EPSILON = 0.0000001f;
    D3DXVECTOR3 edge1 = tri.vP1 - tri.vP0;
    D3DXVECTOR3 edge2 = tri.vP2 - tri.vP0;

    D3DXVECTOR3 h, s, q;
    _float a, f, u, v;

    D3DXVec3Cross(&h, &vRayDir, &edge2);
    a = D3DXVec3Dot(&edge1, &h);

    if (a > -EPSILON && a < EPSILON)
        return false;

    f = 1.0f / a;
    s = vRayOrigin - tri.vP0;
    u = f * D3DXVec3Dot(&s, &h);
    if (u < 0.0f || u > 1.0f)
        return false;

    D3DXVec3Cross(&q, &s, &edge1);
    v = f * D3DXVec3Dot(&vRayDir, &q);
    if (v < 0.0f || u + v > 1.0f)
        return false;

    _float t = f * D3DXVec3Dot(&edge2, &q);
    if (t > EPSILON) // 교차!
    {
        if (outDist)
            *outDist = t;
        return true;
    }
    else // 직선 위에는 있으나 Ray의 시작점 앞이 아님
        return false;
}

CRayCast* CRayCast::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
    return new CRayCast(pGraphic_Device);
}

void CRayCast::Free()
{
    __super::Free();

    Safe_Release(m_pGraphic_Device);
}