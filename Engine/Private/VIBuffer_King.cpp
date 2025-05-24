#include "VIBuffer_King.h"
#include <vector>
#include <cmath>

struct BoxInfo {
    float from[3], to[3];
};

static const BoxInfo king_boxes[] = {
    // from[x, y, z], to[x, y, z] // *** 킹 블록 큐브 좌표, 실제로 MagicaVoxel에서 추출 ***
    // 아래는 예시, 네가 킹의 실루엣에 맞게 추가/수정 가능
    // (실제 기물 형태로 큐브 여러 개 겹치면 됨)
    {{-2, 0, -2}, {2, 1, 2}},    // base
    {{-1, 1, -1}, {1, 5, 1}},    // body lower
    {{-0.5f, 5, -0.5f}, {0.5f, 8, 0.5f}}, // neck
    {{-1.5f, 8, -1.5f}, {1.5f, 9, 1.5f}}, // crown base
    {{-0.3f, 9, -0.3f}, {0.3f, 11, 0.3f}}, // top cross
    // 왕관 점선 부분 추가하고 싶으면 큐브 더 넣어도 됨
};

static const int king_box_count = sizeof(king_boxes) / sizeof(BoxInfo);

CVIBuffer_King::CVIBuffer_King(LPDIRECT3DDEVICE9 pGraphic_Device)
    : CVIBuffer{ pGraphic_Device }
{
}

CVIBuffer_King::CVIBuffer_King(const CVIBuffer_King& Prototype)
    : CVIBuffer{ Prototype }
{
}

HRESULT CVIBuffer_King::Initialize_Prototype()
{
    // 박스별 8정점
    m_iNumVertices = king_box_count * 8;
    m_iVertexStride = sizeof(VTXPOSPAWN);
    m_iFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
    m_ePrimitiveType = D3DPT_TRIANGLELIST;
    m_iNumPrimitive = king_box_count * 12; // 큐브 하나당 12개 삼각형
    m_iNumIndices = m_iNumPrimitive * 3;
    m_iIndexStride = 2;
    m_eIndexFormat = D3DFMT_INDEX16;

    if (FAILED(m_pGraphic_Device->CreateVertexBuffer(
        m_iVertexStride * m_iNumVertices, 0, m_iFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
        return E_FAIL;

    VTXPOSPAWN* pVertices = nullptr;
    m_pVB->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);

    int vtxIdx = 0;
    for (int c = 0; c < king_box_count; ++c) {
        float x0 = king_boxes[c].from[0];
        float y0 = king_boxes[c].from[1];
        float z0 = king_boxes[c].from[2];
        float x1 = king_boxes[c].to[0];
        float y1 = king_boxes[c].to[1];
        float z1 = king_boxes[c].to[2];
        // 8정점
        _float3 verts[8] = {
            {x0, y0, z0}, {x1, y0, z0}, {x1, y1, z0}, {x0, y1, z0},
            {x0, y0, z1}, {x1, y0, z1}, {x1, y1, z1}, {x0, y1, z1}
        };
        for (int vi = 0; vi < 8; ++vi)
            pVertices[vtxIdx + vi].vPosition = verts[vi];
        vtxIdx += 8;
    }
    m_pVB->Unlock();

    if (FAILED(m_pGraphic_Device->CreateIndexBuffer(
        m_iIndexStride * m_iNumIndices, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
        return E_FAIL;

    _ushort* pIndices = nullptr;
    m_pIB->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);

    // 큐브 하나당 삼각형 인덱스(정석)
    const int cube_tris[36] = {
        0,1,2, 0,2,3,   // front
        4,6,5, 4,7,6,   // back
        0,3,7, 0,7,4,   // left
        1,5,6, 1,6,2,   // right
        3,2,6, 3,6,7,   // top
        0,4,5, 0,5,1    // bottom
    };
    int idx = 0;
    for (int c = 0; c < king_box_count; ++c) {
        int base = c * 8;
        for (int ti = 0; ti < 36; ++ti) {
            pIndices[idx++] = base + cube_tris[ti];
        }
    }
    m_pIB->Unlock();

    return S_OK;
}

HRESULT CVIBuffer_King::Initialize(void* pArg)
{
    return S_OK;
}

CVIBuffer_King* CVIBuffer_King::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
    CVIBuffer_King* pInstance = new CVIBuffer_King(pGraphic_Device);

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX(TEXT("Failed to Created : CVIBuffer_King"));
        Safe_Release(pInstance);
    }

    return pInstance;
}

CComponent* CVIBuffer_King::Clone(void* pArg)
{
    CVIBuffer_King* pInstance = new CVIBuffer_King(*this);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX(TEXT("Failed to Cloned : CVIBuffer_King"));
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CVIBuffer_King::Free()
{
    __super::Free();
}
