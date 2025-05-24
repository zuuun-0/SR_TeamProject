#include "VIBuffer_Queen.h"

CVIBuffer_Queen::CVIBuffer_Queen(LPDIRECT3DDEVICE9 DEVICE)
	: CVIBuffer(DEVICE)
{}

CVIBuffer_Queen::CVIBuffer_Queen(const CVIBuffer_Queen& OTHDER)
	: CVIBuffer(OTHDER)
{}

HRESULT CVIBuffer_Queen::Initialize_Prototype()
{
	const _uint iRow = 30;
	const _uint iCol = iRow - 1;

	m_iRow = iRow;
	m_iCol = iCol;

	// 정점 개수: 각 단면 6개 + 꼭짓점 1개
	m_iNumVertices = (iRow + 1) * 6 + 1;
	m_iVertexStride = sizeof(VTXPOSPAWN);
	m_iFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;

	// 삼각형 개수 = 아래(4*31) + 측면(12*30) + 위(6)
	m_iNumPrimitive = (iRow + 1) * 4 + (iCol + 1) * 12 + 6;
	m_iIndexStride = 2;
	m_iNumIndices = m_iNumPrimitive * 3;
	m_eIndexFormat = D3DFMT_INDEX16;

	if(FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iVertexStride * m_iNumVertices, 0, m_iFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;

	VTXPOSPAWN* pVertices = nullptr;
	m_pVB->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);

	// ---------------------------
	// 폭, 높이 설정
	// ---------------------------
	_float arWidth[] = {
		0.1f, 0.1f, 0.1f,
		0.4f, 0.4f, 0.4f,
		0.3f, 0.3f,
		0.7f, 0.2f, 0.3f, 0.3f,
		0.35f, 0.35f, 0.35f,
		0.4f, 0.4f, 0.4f, 0.4f,
		0.45f, 0.45f, 0.45f,
		0.5f, 0.5f, 0.5f,
		1.0f, 0.95f, 0.9f,
		0.4f
	};
	_float arHeight[] = {
		0.01f, 0.03f, 0.01f,
		0.05f, 0.1f, 0.05f,
		0.05f, 0.05f,
		0.05f, 0.05f, 0.05f, 0.05f,
		0.05f, 0.05f, 0.05f,
		0.07f, 0.07f, 0.07f, 0.07f,
		0.05f, 0.05f, 0.05f,
		0.05f, 0.05f, 0.05f,
		0.05f, 0.05f, 0.05f,
		0.01f
	};

	const _float fWidthRatio = 2.0f;
	const _float fHeightRatio = 5.0f;

	_float y = 0.f;
	_uint iIndex = 0;

	for(_int i = iRow; i >= 0; --i)
	{
		_float fDiameter = arWidth[i] * fWidthRatio;
		_float fLength = fDiameter * sinf(D3DXToRadian(60.f));

		pVertices[iIndex++].vPosition = _float3(-fDiameter, y, 0.f);
		pVertices[iIndex++].vPosition = _float3(-fDiameter / 2, y, -fLength);
		pVertices[iIndex++].vPosition = _float3(fDiameter / 2, y, -fLength);
		pVertices[iIndex++].vPosition = _float3(fDiameter, y, 0.f);
		pVertices[iIndex++].vPosition = _float3(fDiameter / 2, y, fLength);
		pVertices[iIndex++].vPosition = _float3(-fDiameter / 2, y, fLength);

		y += arHeight[i] * fHeightRatio;
	}

	// 꼭짓점 추가
	pVertices[iIndex++].vPosition = _float3(0.f, y, 0.f);
	m_pVB->Unlock();

	// ---------------------------
	// 인덱스 버퍼
	// ---------------------------
	if(FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iIndexStride * m_iNumIndices, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
		return E_FAIL;

	_ushort* pIndices = nullptr;
	m_pIB->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);
	iIndex = 0;

	// 아래 면 구성 (row + 1 줄, 각 줄 4개 삼각형)
	for(_uint i = 0; i <= m_iNumVertices - 7; i += 6)
	{
		for(_uint j = 0; j < 4; ++j)
		{
			assert(iIndex + 3 <= m_iNumIndices);
			pIndices[iIndex++] = i;
			pIndices[iIndex++] = 2 + i + j;
			pIndices[iIndex++] = 1 + i + j;
		}
	}

	// 측면 구성
	_uint iCnt = 6;
	for(_uint i = 0; i < iCol + 1; ++i)
	{
		for(_uint j = 0; j < 6; ++j)
		{
			if(j != 5)
			{
				assert(iIndex + 6 <= m_iNumIndices);
				pIndices[iIndex++] = iCnt;
				pIndices[iIndex++] = iCnt + 1;
				pIndices[iIndex++] = iCnt - 5;

				pIndices[iIndex++] = iCnt;
				pIndices[iIndex++] = iCnt - 5;
				pIndices[iIndex++] = iCnt - 6;
			}
			else
			{
				pIndices[iIndex++] = iCnt;
				pIndices[iIndex++] = iCnt - 5;
				pIndices[iIndex++] = iCnt - 11;

				pIndices[iIndex++] = iCnt;
				pIndices[iIndex++] = iCnt - 11;
				pIndices[iIndex++] = iCnt - 6;
			}
			++iCnt;
		}
	}

	// 윗면: 마지막 링 → 꼭짓점
	_ushort topIndex = (_ushort)(m_iNumVertices - 1);
	_ushort ringStart = (_ushort)(m_iNumVertices - 7);
	for(_uint i = 0; i < 6; ++i)
	{
		pIndices[iIndex++] = ringStart + i;
		pIndices[iIndex++] = ringStart + ((i + 1) % 6);
		pIndices[iIndex++] = topIndex;
	}

	assert(iIndex == m_iNumIndices);
	m_pIB->Unlock();

	return S_OK;
}




HRESULT CVIBuffer_Queen::Initialize(void* pArg)
{
	return S_OK;
}

CVIBuffer_Queen* CVIBuffer_Queen::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Queen* newObj = new CVIBuffer_Queen(pGraphic_Device);

	if(FAILED(newObj->Initialize_Prototype()))
	{
		assert(false);
		Safe_Release(newObj);
	}
	return newObj;
}

CComponent* CVIBuffer_Queen::Clone(void* pArg)
{
	CVIBuffer_Queen* pInstance = new CVIBuffer_Queen(*this);

	if(FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CVI_Buffer_Queen"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
void CVIBuffer_Queen::Free()
{
	Safe_Release(m_pVB);
	//Safe_Release(m_pIB);
}