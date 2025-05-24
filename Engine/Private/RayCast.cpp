#include "RayCast.h"

CRayCast::CRayCast(LPDIRECT3DDEVICE9 pGrahpic_Device)
    : m_pGraphic_Device{ pGrahpic_Device }
{
    Safe_AddRef(m_pGraphic_Device);
}

HRESULT CRayCast::ScreenPosToRay(POINT ptMouse)
{
    _float4x4 matProj = {};

    _float3 vProj = {};

    D3DVIEWPORT9 ViewPort = {};



    return S_OK;
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