#include "VIBuffer_Rook.h"

CVIBuffer_Rook::CVIBuffer_Rook(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer{ pGraphic_Device }
{
}

CVIBuffer_Rook::CVIBuffer_Rook(const CVIBuffer_Rook& Prototype)
	: CVIBuffer{ Prototype }
{
}

HRESULT CVIBuffer_Rook::Initialize_Prototype()
{
    struct Profile { float y, r; };
    Profile profile[] = {
        { 0.00f, 1.12f },
        { 0.08f, 1.12f },
        { 0.15f, 0.92f },
        { 0.29f, 0.82f },
        { 0.44f, 0.62f },
        { 0.68f, 0.60f },
        { 0.89f, 0.78f },
        { 1.00f, 0.83f },
        { 1.17f, 0.67f },
        { 1.24f, 1.06f },
        { 1.34f, 1.06f }
    };
    const int profileCount = sizeof(profile) / sizeof(Profile);

    const int latheSegments = 90;
    const int crownTeeth = 12; // »ç°¢Çü Åé´Ï ´À³¦¿£ 8~14 Á¤µµ ÃßÃµ
    const float scaleY = 2.4f;
    const float toothWidthRatio = 0.5f; // 0.5¸é 1:1(Åé´Ï:È¨), ´õ ÀÛÀ¸¸é ´õ ¾ãÀº Åé´Ï

    m_iNumVertices = profileCount * latheSegments;
    m_iVertexStride = sizeof(VTXPOSPAWN);
    m_iFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
    m_ePrimitiveType = D3DPT_TRIANGLELIST;

    m_iNumPrimitive = (profileCount - 1) * latheSegments * 2;
    m_iIndexStride = 2;
    m_iNumIndices = m_iNumPrimitive * 3;
    m_eIndexFormat = D3DFMT_INDEX16;

    // --- Vertex Buffer ---
    if (FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iVertexStride * m_iNumVertices, 0, m_iFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
        return E_FAIL;

    VTXPOSPAWN* pVertices = nullptr;
    m_pVB->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);

    const float toothAngle = 360.0f / crownTeeth;

    for (int i = 0; i < profileCount; ++i)
    {
        for (int seg = 0; seg < latheSegments; ++seg)
        {
            float angle = D3DXToRadian(seg * 360.0f / latheSegments);
            float y = profile[i].y * scaleY;
            float r = profile[i].r;

            // ¿Õ°ü À­´Ü¸¸ »ç°¢Çü Åé´Ï·Î Ã³¸®
            if (i == profileCount - 1) {
                float angleDeg = seg * 360.0f / latheSegments;
                int toothIdx = int(angleDeg / toothAngle);
                float angleInTooth = angleDeg - (toothIdx * toothAngle);
                bool isTooth = (angleInTooth < toothAngle * toothWidthRatio);
                if (!isTooth)
                    y = profile[i - 1].y * scaleY; // È¨Àº ¾Æ·§´Ü y·Î!
            }

            float x = cosf(angle) * r;
            float z = sinf(angle) * r;
            pVertices[i * latheSegments + seg].vPosition = _float3(x, y, z);
        }
    }

    m_pVB->Unlock();

    // --- Index Buffer ---
    if (FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iIndexStride * m_iNumIndices, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
        return E_FAIL;

    _ushort* pIndices = nullptr;
    m_pIB->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);

    int idx = 0;
    for (int i = 0; i < profileCount - 1; ++i)
    {
        for (int seg = 0; seg < latheSegments; ++seg)
        {
            int next = (seg + 1) % latheSegments;

            int a = i * latheSegments + seg;
            int b = (i + 1) * latheSegments + seg;
            int c = (i + 1) * latheSegments + next;
            int d = i * latheSegments + next;

            // µÎ »ï°¢Çü (a,b,c) (a,c,d)
            pIndices[idx++] = a;
            pIndices[idx++] = b;
            pIndices[idx++] = c;
            pIndices[idx++] = a;
            pIndices[idx++] = c;
            pIndices[idx++] = d;
        }
    }
    m_pIB->Unlock();

    return S_OK;
}



HRESULT CVIBuffer_Rook::Initialize(void* pArg)
{
	return S_OK;
}

CVIBuffer_Rook* CVIBuffer_Rook::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Rook* pInstance = new CVIBuffer_Rook(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CVIBuffer_Rook"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CVIBuffer_Rook::Clone(void* pArg)
{
	CVIBuffer_Rook* pInstance = new CVIBuffer_Rook(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CVIBuffer_Rook"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Rook::Free()
{
	__super::Free();
}
