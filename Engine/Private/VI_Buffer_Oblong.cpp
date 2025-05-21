#include "VI_Buffer_Oblong.h"

CVIBuffer_Oblong::CVIBuffer_Oblong(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{}

CVIBuffer_Oblong::CVIBuffer_Oblong(const CVIBuffer_Oblong& Prototype)
	: CVIBuffer(Prototype)
{}

HRESULT CVIBuffer_Oblong::Initialize_Prototype()
{
	m_iNumVertices = 24;
	m_iVertexStride = sizeof(VTXPOSTEX);
	m_iFVF = VTXPOSTEX::FVF;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = 12;

	m_iIndexStride = 2;
	m_iNumIndices = 36;
	m_eIndexFormat = D3DFMT_INDEX16;

	// 정점 버퍼 생성
	if(FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iVertexStride * m_iNumVertices, 0, m_iFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;

	VTXPOSTEX* pVertices = nullptr;
	m_pVB->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);

	const float L = -0.5f, R = 0.5f, T = 1.f, B = -1.f, F = 0.5f, N = -0.5f;

	// 6면 × 4정점
	// 앞면
	pVertices[0] = { {L, T, N}, {0.f, 0.f} };
	pVertices[1] = { {R, T, N}, {1.f, 0.f} };
	pVertices[2] = { {R, B, N}, {1.f, 1.f} };
	pVertices[3] = { {L, B, N}, {0.f, 1.f} };

	pVertices[0] = { {L, T, N}, {0.f, 0.f} }; // 좌상
	pVertices[1] = { {R, T, N}, {1.f, 0.f} }; // 우상
	pVertices[2] = { {R, B, N}, {1.f, 1.f} }; // 우하
	pVertices[3] = { {L, B, N}, {0.f, 1.f} };
	// 뒷면
	pVertices[4] = { {R, T, F}, {0.f, 0.f} };
	pVertices[5] = { {L, T, F}, {1.f, 0.f} };
	pVertices[6] = { {L, B, F}, {1.f, 1.f} };
	pVertices[7] = { {R, B, F}, {0.f, 1.f} };

	// 왼쪽면
	pVertices[8]  = { {L, T, F}, {0.f, 0.f} };
	pVertices[9]  = { {L, T, N}, {1.f, 0.f} };
	pVertices[10] = { {L, B, N}, {1.f, 1.f} };
	pVertices[11] = { {L, B, F}, {0.f, 1.f} };

	// 오른쪽면
	pVertices[12] = { {R, T, N}, {0.f, 0.f} };
	pVertices[13] = { {R, T, F}, {1.f, 0.f} };
	pVertices[14] = { {R, B, F}, {1.f, 1.f} };
	pVertices[15] = { {R, B, N}, {0.f, 1.f} };

	// 윗면
	pVertices[16] = { {L, T, F}, {0.f, 0.f} };
	pVertices[17] = { {R, T, F}, {1.f, 0.f} };
	pVertices[18] = { {R, T, N}, {1.f, 1.f} };
	pVertices[19] = { {L, T, N}, {0.f, 1.f} };

	// 아랫면
	pVertices[20] = { {L, B, N}, {0.f, 0.f} };
	pVertices[21] = { {R, B, N}, {1.f, 0.f} };
	pVertices[22] = { {R, B, F}, {1.f, 1.f} };
	pVertices[23] = { {L, B, F}, {0.f, 1.f} };

	m_pVB->Unlock();

	// 인덱스 버퍼 생성
	if(FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iIndexStride * m_iNumIndices, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
		return E_FAIL;

	_ushort* pIndices = nullptr;
	m_pIB->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);

	_ushort idx = 0;
	for(int i = 0; i < 6; ++i)
	{
		pIndices[i * 6 + 0] = idx + 0;
		pIndices[i * 6 + 1] = idx + 1;
		pIndices[i * 6 + 2] = idx + 2;

		pIndices[i * 6 + 3] = idx + 0;
		pIndices[i * 6 + 4] = idx + 2;
		pIndices[i * 6 + 5] = idx + 3;

		idx += 4;
	}

	m_pIB->Unlock();

	return S_OK;
}

CVIBuffer_Oblong* CVIBuffer_Oblong::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Oblong* pInstance = new CVIBuffer_Oblong(pGraphic_Device);

	if(FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CVIBuffer_Oblong"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

HRESULT CVIBuffer_Oblong::Initialize(void* pArg)
{
	return S_OK;
}

CComponent* CVIBuffer_Oblong::Clone(void* pArg)
{
	CVIBuffer_Oblong* pInstance = new CVIBuffer_Oblong(*this);

	if(FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CVIBuffer_Oblong"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Oblong::Free()
{
	__super::Free();
}
