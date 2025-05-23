#include "VIBuffer_Knight.h"
#include <set>
#include <tuple>

CVIBuffer_Knight::CVIBuffer_Knight(LPDIRECT3DDEVICE9 pGraphic_Device)
    : CVIBuffer{ pGraphic_Device }
{
}

CVIBuffer_Knight::CVIBuffer_Knight(const CVIBuffer_Knight& Prototype)
    : CVIBuffer{ Prototype }
{
}

HRESULT CVIBuffer_Knight::Initialize_Prototype()
{
    // Blockbench 모델 그대로, float 좌표로 박스 생성
    struct BoxInfo {
        float from[3], to[3], angle;
        char axis;
        float origin[3];
    };

    std::vector<BoxInfo> knight_boxes = {
        // {from[x,y,z], to[x,y,z], angle, axis, origin[x,y,z]}
        {{9, 11.87284, 6.88519}, {10, 13.87284, 7.88519}, 22.5f, 'x', {9.5, 12.87284, 7.38519}},
        {{6, 11.87284, 6.88519}, {7, 13.87284, 7.88519}, 22.5f, 'x', {6.5, 12.87284, 7.38519}},
        {{7, 12.15, 5}, {9, 13.15, 9}, 0.f, 'n', {0,0,0}},
        {{7, 10.15, 9}, {9, 12.15, 11}, 0.f, 'n', {0,0,0}},
        {{7, 3.15, 11}, {9, 10.15, 12}, 0.f, 'n', {0,0,0}},
        {{7, 7.85711, 3.29289}, {9, 11.85711, 5.29289}, 45.f, 'x', {8, 9.85711, 4.29289}},
        {{6, 9.30697, 4.45995}, {10, 12.08197, 5.60995}, -22.5f, 'x', {8, 10.58197, 5.10995}},
        {{6, 9.15, 5}, {10, 12.15, 9}, 0.f, 'n', {0,0,0}},
        {{6, 10.15, 9}, {10, 11.15, 10}, 0.f, 'n', {0,0,0}},
        {{6, 7.15, 7}, {10, 10.15, 11}, 0.f, 'n', {0,0,0}},
        {{6, 6.15, 6}, {10, 7.15, 11}, 0.f, 'n', {0,0,0}},
        {{6, 3.15, 5}, {10, 6.15, 11}, 0.f, 'n', {0,0,0}},
        {{7, 2, 6}, {9, 4, 10}, 0.f, 'n', {0,0,0}},
        {{6, 2, 7}, {10, 4, 9}, 0.f, 'n', {0,0,0}},
        {{6, 1, 5}, {10, 2, 11}, 0.f, 'n', {0,0,0}},
        {{5, 1, 6}, {11, 2, 10}, 0.f, 'n', {0,0,0}},
        {{5, 0, 4}, {11, 1, 12}, 0.f, 'n', {0,0,0}},
        {{4, 0, 5}, {12, 1, 11}, 0.f, 'n', {0,0,0}}
    };

    // 전체 큐브 개수
    int cubeCount = static_cast<int>(knight_boxes.size());
    float cubeBox[64][8]; // x, y, z, w, h, d, angle, axis

    for (int i = 0; i < cubeCount; ++i) {
        // 박스 중심좌표 계산
        cubeBox[i][0] = (knight_boxes[i].from[0] + knight_boxes[i].to[0]) * 0.5f;
        cubeBox[i][1] = (knight_boxes[i].from[1] + knight_boxes[i].to[1]) * 0.5f;
        cubeBox[i][2] = (knight_boxes[i].from[2] + knight_boxes[i].to[2]) * 0.5f;
        cubeBox[i][3] = std::abs(knight_boxes[i].to[0] - knight_boxes[i].from[0]);
        cubeBox[i][4] = std::abs(knight_boxes[i].to[1] - knight_boxes[i].from[1]);
        cubeBox[i][5] = std::abs(knight_boxes[i].to[2] - knight_boxes[i].from[2]);
        cubeBox[i][6] = knight_boxes[i].angle;
        cubeBox[i][7] = knight_boxes[i].axis;
        // origin/회전축 등도 knight_boxes에서 꺼내 쓸 수 있음
    }

    // 아래 버퍼 세팅 부분
    m_iNumVertices = cubeCount * 8;
    m_iVertexStride = sizeof(VTXPOSPAWN);
    m_iFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
    m_ePrimitiveType = D3DPT_TRIANGLELIST;
    m_iNumPrimitive = cubeCount * 12;
    m_iIndexStride = 2;
    m_iNumIndices = m_iNumPrimitive * 3;
    m_eIndexFormat = D3DFMT_INDEX16;

    if (FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iVertexStride * m_iNumVertices, 0, m_iFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
        return E_FAIL;

    VTXPOSPAWN* pVertices = nullptr;
    m_pVB->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);

    int vtxIdx = 0;
    for (int c = 0; c < cubeCount; ++c) {
        float cx = cubeBox[c][0];
        float cy = cubeBox[c][1];
        float cz = cubeBox[c][2];
        float sx = cubeBox[c][3] * 0.5f;
        float sy = cubeBox[c][4] * 0.5f;
        float sz = cubeBox[c][5] * 0.5f;

        // 기본 8 정점
        _float3 verts[8] = {
            _float3(cx - sx, cy - sy, cz - sz),
            _float3(cx + sx, cy - sy, cz - sz),
            _float3(cx + sx, cy + sy, cz - sz),
            _float3(cx - sx, cy + sy, cz - sz),
            _float3(cx - sx, cy - sy, cz + sz),
            _float3(cx + sx, cy - sy, cz + sz),
            _float3(cx + sx, cy + sy, cz + sz),
            _float3(cx - sx, cy + sy, cz + sz),
        };

        // rotation 적용 (x/y축만, 근사)
        if (cubeBox[c][6] != 0.f) {
            float angleRad = cubeBox[c][6] * 3.14159265f / 180.0f;
            char axis = static_cast<char>(cubeBox[c][7]);
            // 회전 origin은 knight_boxes[c].origin
            float ox = knight_boxes[c].origin[0];
            float oy = knight_boxes[c].origin[1];
            float oz = knight_boxes[c].origin[2];
            for (int vi = 0; vi < 8; ++vi) {
                float x = verts[vi].x - ox;
                float y = verts[vi].y - oy;
                float z = verts[vi].z - oz;
                float rx = x, ry = y, rz = z;
                if (axis == 'x') {
                    ry = y * cos(angleRad) - z * sin(angleRad);
                    rz = y * sin(angleRad) + z * cos(angleRad);
                }
                else if (axis == 'y') {
                    rx = x * cos(angleRad) + z * sin(angleRad);
                    rz = -x * sin(angleRad) + z * cos(angleRad);
                }
                verts[vi] = _float3(rx + ox, ry + oy, rz + oz);
            }
        }

        for (int vi = 0; vi < 8; ++vi)
            pVertices[vtxIdx + vi].vPosition = verts[vi];

        vtxIdx += 8;
    }
    m_pVB->Unlock();

    if (FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iIndexStride * m_iNumIndices, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
        return E_FAIL;

    _ushort* pIndices = nullptr;
    m_pIB->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);

    int idx = 0;
    for (int c = 0; c < cubeCount; ++c) {
        int base = c * 8;
        pIndices[idx++] = base + 0; pIndices[idx++] = base + 1; pIndices[idx++] = base + 2;
        pIndices[idx++] = base + 0; pIndices[idx++] = base + 2; pIndices[idx++] = base + 3;
        pIndices[idx++] = base + 4; pIndices[idx++] = base + 6; pIndices[idx++] = base + 5;
        pIndices[idx++] = base + 4; pIndices[idx++] = base + 7; pIndices[idx++] = base + 6;
        pIndices[idx++] = base + 0; pIndices[idx++] = base + 3; pIndices[idx++] = base + 7;
        pIndices[idx++] = base + 0; pIndices[idx++] = base + 7; pIndices[idx++] = base + 4;
        pIndices[idx++] = base + 1; pIndices[idx++] = base + 5; pIndices[idx++] = base + 6;
        pIndices[idx++] = base + 1; pIndices[idx++] = base + 6; pIndices[idx++] = base + 2;
        pIndices[idx++] = base + 3; pIndices[idx++] = base + 2; pIndices[idx++] = base + 6;
        pIndices[idx++] = base + 3; pIndices[idx++] = base + 6; pIndices[idx++] = base + 7;
        pIndices[idx++] = base + 0; pIndices[idx++] = base + 4; pIndices[idx++] = base + 5;
        pIndices[idx++] = base + 0; pIndices[idx++] = base + 5; pIndices[idx++] = base + 1;
    }
    m_pIB->Unlock();

    return S_OK;
}


HRESULT CVIBuffer_Knight::Initialize(void* pArg)
{
    return S_OK;
}

CVIBuffer_Knight* CVIBuffer_Knight::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
    CVIBuffer_Knight* pInstance = new CVIBuffer_Knight(pGraphic_Device);

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX(TEXT("Failed to Created : CVIBuffer_Knight"));
        Safe_Release(pInstance);
    }

    return pInstance;
}

CComponent* CVIBuffer_Knight::Clone(void* pArg)
{
    CVIBuffer_Knight* pInstance = new CVIBuffer_Knight(*this);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX(TEXT("Failed to Cloned : CVIBuffer_Knight"));
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CVIBuffer_Knight::Free()
{
    __super::Free();
}
