#include "VIBuffer_Board.h"

CVIBuffer_Board::CVIBuffer_Board(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer{ pGraphic_Device }
{
}

CVIBuffer_Board::CVIBuffer_Board(const CVIBuffer_Board& Prototype)
	: CVIBuffer{ Prototype }
{
}

HRESULT CVIBuffer_Board::Initialize_Prototype(_uint iNumVerticesX, _uint iNumVerticesZ)
{
	m_iNumVerticesX = iNumVerticesX;
	m_iNumVerticesY = iNumVerticesZ;

	m_iNumVertices = iNumVerticesX * iNumVerticesZ;
	m_iVertexStride = sizeof(VTXPOSTEX);
	m_iFVF = D3DFVF_XYZ | D3DFVF_TEX1;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = ((iNumVerticesX ) * (iNumVerticesZ )) * 2;

	m_iNumIndices = m_iNumPrimitive * 3;
	m_iIndexStride = 2;
	m_eIndexFormat = D3DFMT_INDEX16;

#pragma region VERTEX_BUFFER
	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iNumVertices * m_iVertexStride, 0, m_iFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;

	VTXPOSTEX* pVertices = { nullptr };

	m_pVB->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);

	for (_uint i = 0; i < iNumVerticesZ; i++)
	{
		for (_uint j = 0; j < iNumVerticesX; j++)
		{
			_uint iIndex = i * iNumVerticesX + j;

			pVertices[iIndex].vPosition = _float3(_float(j), 0.f, _float(i));
			pVertices[iIndex].vTexcoord = _float2(static_cast<_float>(j) / (iNumVerticesX - 1), static_cast<_float>(i) / (iNumVerticesZ-1));
		}
	}

	m_pVB->Unlock();
#pragma endregion


#pragma region INDEX_BUFFER
	if (FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iNumIndices * m_iIndexStride, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
		return E_FAIL;

	_ushort* pIndices = { nullptr };

	_ushort iCnt = { 0 };

	m_pIB->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);

	for (_uint i = 0; i < iNumVerticesZ - 1; i++)
	{
		for (_uint j = 0; j < iNumVerticesX - 1; j++)
		{
			// X 버텍스 100개, Y 버텍스 100개
			_uint iIndex = (i * iNumVerticesX) + j;

			_uint iIndices[4] =
			{
				iIndex + m_iNumVerticesX,
				iIndex + m_iNumVerticesX + 1,
				iIndex + 1,
				iIndex
			};

			pIndices[iCnt++] = iIndices[0];
			pIndices[iCnt++] = iIndices[1];
			pIndices[iCnt++] = iIndices[2];

			pIndices[iCnt++] = iIndices[0];
			pIndices[iCnt++] = iIndices[2];
			pIndices[iCnt++] = iIndices[3];

			// 0, 1, 2, 3, 4, 5 : 인덱스의 그 머시기 거시기 ㅇㅇ 6개
		}
	}

	m_pIB->Unlock();
#pragma endregion

	return S_OK;
}

HRESULT CVIBuffer_Board::Initialize(void* pArg)
{
	return S_OK;
}

CVIBuffer_Board* CVIBuffer_Board::Create(LPDIRECT3DDEVICE9 pGraphic_Device, _uint iNumVerticesX, _uint iNumVerticesZ)
{
	CVIBuffer_Board* pInstance = new CVIBuffer_Board(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype(iNumVerticesX, iNumVerticesZ)))
	{
		MSG_BOX(TEXT("Failed to Created : CVIBuffer_Board"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CVIBuffer_Board::Clone(void* pArg)
{
	CVIBuffer_Board* pInstance = new CVIBuffer_Board(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CVIBuffer_Board"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Board::Free()
{
	__super::Free();
}
