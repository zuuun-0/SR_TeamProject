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

	m_iNumVertices = (iRow + 1) * 6 + 1;
	m_iVertexStride = sizeof(VTXPOSPAWN);
	m_iFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = m_iRow * 4 + m_iCol * 12 + 6;
	m_iIndexStride = 2;
	m_iNumIndices = m_iNumPrimitive * 3;
	m_eIndexFormat = D3DFMT_INDEX16;

	if(FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iVertexStride * m_iNumVertices, 0, m_iFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;

	VTXPOSPAWN* pVertices = nullptr;
	m_pVB->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);

	// arWidth 수정
	_float arWidth[iRow + 1] = {
		0.1f, 0.1f, 0.1f,                      // 머리 상단 구간
		0.4f, 0.4f, 0.4f,                    // 목 구간
		0.3f, 0.3f,                          // 어깨 상단 구간
		0.7f, 0.2f, 0.3f, 0.3f,              // 어깨 하단 ~ 몸통 상단
		0.35f, 0.35f, 0.35f,                    // 허리 들어가는 부분 (허리 시작)
		0.4f, 0.4f, 0.4f, 0.4f,              // 허리에서 다시 벌어지는 부분 (몸통 하단)
		0.45f, 0.45f, 0.45f,                    // 베이스 상단
		0.5f, 0.5f, 0.5f,                   // 베이스 중간
		1.0f, 0.95f, 0.9f,                    // 베이스 하단
		0.4f                                  // 받침대
	};

	_float arHeight[iRow + 1] = {
			0.01f, 0.03f, 0.01f,                  // 머리 상단
			0.05f, 0.1f, 0.05f,                 // 목 구간
			0.05f, 0.05f,                        // 어깨 상단
			0.05f, 0.05f, 0.05f, 0.05f,          // 몸통 상단
			0.05f, 0.05f, 0.05f,                 // 허리 시작
			0.07f, 0.07f, 0.07f, 0.07f,          // 허리에서 벌어짐 ~ 몸통 하단
			0.05f, 0.05f, 0.05f,                 // 베이스 상단
			0.05f, 0.05f, 0.05f,                 // 베이스 중간
			0.05f, 0.05f, 0.05f,                 // 베이스 하단
			0.01f                                 // 받침대
	};

	const _float fWidthRatio = 2.0f;
	const _float fHeightRatio = 5.0f;

	_float fDiameter = 0.f;
	_float fHeight = 0.f;
	_float fLength = 0.f;
	_uint iIndex = 0;

	_float y = 0.f;
	for(_int i = iRow; i >= 0; --i)
	{
		fDiameter = arWidth[i] * fWidthRatio;
		fLength = fDiameter * sinf(D3DXToRadian(60.f));

		pVertices[iIndex++].vPosition = _float3(-fDiameter, y, 0.f);
		pVertices[iIndex++].vPosition = _float3(-fDiameter / 2, y, -fLength);
		pVertices[iIndex++].vPosition = _float3(fDiameter / 2, y, -fLength);
		pVertices[iIndex++].vPosition = _float3(fDiameter, y, 0.f);
		pVertices[iIndex++].vPosition = _float3(fDiameter / 2, y, fLength);
		pVertices[iIndex++].vPosition = _float3(-fDiameter / 2, y, fLength);

		y += arHeight[i] * fHeightRatio;
	}

	pVertices[iIndex++].vPosition = _float3(0.f, y, 0.f);
	m_pVB->Unlock();

	if(FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iIndexStride * m_iNumIndices, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
		return E_FAIL;

	_ushort* pIndices = nullptr;
	m_pIB->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);

	_uint iCnt = 0;
	iIndex = 0;

	for(_uint i = 0; i < m_iNumVertices - 7; i += 6)
	{
		for(_uint j = 0; j < 4; ++j)
		{
			pIndices[iIndex++] = i;
			pIndices[iIndex++] = 2 + i + j;
			pIndices[iIndex++] = 1 + i + j;
		}
	}

	iCnt = 6;
	for(_uint i = 0; i < iCol + 1; ++i)
	{
		for(_uint j = 0; j < 6; ++j)
		{
			if(j != 5)
			{
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

	_ushort topIndex = (_ushort)(m_iNumVertices - 1);
	_ushort ringStart = (_ushort)(m_iNumVertices - 7);
	for(_uint i = 0; i < 6; ++i)
	{
		pIndices[iIndex++] = ringStart + i;
		pIndices[iIndex++] = ringStart + ((i + 1) % 6);
		pIndices[iIndex++] = topIndex;
	}

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