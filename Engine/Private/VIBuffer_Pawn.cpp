#include "VIBuffer_Pawn.h"

CVIBuffer_Pawn::CVIBuffer_Pawn(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer{ pGraphic_Device }
{
}

CVIBuffer_Pawn::CVIBuffer_Pawn(const CVIBuffer_Pawn& Prototype)
	: CVIBuffer { Prototype }
	, m_tAABB { Prototype.m_tAABB }
{
}

HRESULT CVIBuffer_Pawn::Initialize_Prototype()
{
	const _uint iRow = { 25 };
	const _uint iCol = { iRow - 1 };

	m_iRow = iRow;
	m_iCol = iCol;

	m_iNumVertices = m_iRow * 6;
	m_iVertexStride = sizeof(VTXPOSPAWN);
	m_iFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = 4 * 2 + m_iCol * 12;

	m_iIndexStride = 2;
	m_iNumIndices = m_iNumPrimitive * 3;
	m_eIndexFormat = D3DFMT_INDEX16;


#pragma region VERTEX_BUFFER
	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iVertexStride * m_iNumVertices, 0, m_iFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;

	VTXPOSPAWN* pVertices = { nullptr };

	m_pVB->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);

#pragma region VERTICES_POSITION

	_uint iIndex = { 0 };

	_float fLength = { 0.f };
	_float fHeight = { 0.f };
	_float fDiameter = { 0.f };

	_float fWidthRatio = { 2.f };
	_float fHeightRatio = { 0.4f };

	_float arWidth[iRow] =
	{
		1.0f, 0.956f, 0.721f, 0.857f, 0.784f,
		0.609f, 0.37f, 0.787f, 0.896f, 0.263f,
		0.419f, 0.529f, 0.604f, 0.672f, 0.706f,
		0.742f, 0.74f, 0.727f, 0.706f, 0.659f,
		0.622f, 0.549f, 0.464f, 0.354f, 0.193f
	};

	_float arHeight[iRow] = {
		0.f, 1.0f, 0.792f, 0.519f, 0.844f,
		0.844f,	4.662f, 0.f, 0.675f, 0.909f,
		0.39f,	0.429f, 0.506f, 0.481f, 0.519f,
		0.545f,	0.532f, 0.532f, 0.519f, 0.468f,
		0.494f,	0.377f, 0.416f, 0.39f, 0.2f
	};

	for (size_t i = 0; i < m_iRow; i++)
	{
		if (9 == i)		// 여기부터 헤드 - 비율 수정
		{
			fWidthRatio *= 0.8f;
			fHeightRatio *= 0.8f;
		}

		fDiameter = arWidth[i] * fWidthRatio;
		fHeight += arHeight[i] * fHeightRatio;

		fLength = fDiameter * sinf(D3DXToRadian(60.f));

		pVertices[iIndex++].vPosition = _float3(-fDiameter, fHeight, 0.f);				// 0
		pVertices[iIndex++].vPosition = _float3(-fDiameter / 2, fHeight, -fLength);		// 1
		pVertices[iIndex++].vPosition = _float3(fDiameter / 2, fHeight, -fLength);		// 2
		pVertices[iIndex++].vPosition = _float3(fDiameter, fHeight, 0.f);				// 3
		pVertices[iIndex++].vPosition = _float3(fDiameter / 2, fHeight, fLength);		// 4
		pVertices[iIndex++].vPosition = _float3(-fDiameter / 2, fHeight, fLength);		// 5
	}

#pragma endregion

	m_pVB->Unlock();

#pragma endregion


#pragma region INDEX_BUFFER
	if (FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iIndexStride * m_iNumIndices, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
		return E_FAIL;

	_ushort* pIndices = { nullptr };

	m_pIB->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);


	_uint iCnt = { 0 };
	iIndex = 0;

	for (_uint i = 0; i <= m_iNumVertices; i += m_iNumVertices)
	{
		if (0 == i)
		{
			for (_uint j = 0; j < 4; j++)
			{
				pIndices[iIndex++] = iCnt;
				pIndices[iIndex++] = 1 + iCnt + j;
				pIndices[iIndex++] = 2 + iCnt + j;
			}
		}
		else if (0 != i)
		{
			iCnt += m_iNumVertices - 6;

			for (_uint j = 0; j < 4; j++)
			{
				pIndices[iIndex++] = iCnt;
				pIndices[iIndex++] = 2 + iCnt + j;
				pIndices[iIndex++] = 1 + iCnt + j;
			}
		}

		// 가로 면

		if (iIndex == (2 * 4) * 3)
			break;
	}

	iCnt = 6;

	for (_uint i = 0; i < m_iCol; i++)	// 0, 1, 2, 3
	{
		for (_uint j = 0; j < 6; j++)
		{
			if (j != 5)
			{
				// 6
				pIndices[iIndex++] = iCnt;
				pIndices[iIndex++] = iCnt + 1;
				pIndices[iIndex++] = iCnt - 5;

				pIndices[iIndex++] = iCnt;
				pIndices[iIndex++] = iCnt - 5;
				pIndices[iIndex++] = iCnt - 6;
			}
			else
			{
				// 11
				pIndices[iIndex++] = iCnt;
				pIndices[iIndex++] = iCnt - 5;
				pIndices[iIndex++] = iCnt - 11;

				pIndices[iIndex++] = iCnt;
				pIndices[iIndex++] = iCnt - 11;
				pIndices[iIndex++] = iCnt - 6;
			}

			++iCnt;
		}
	};

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_Pawn::Initialize(void* pArg)
{
	return S_OK;
}

CVIBuffer_Pawn* CVIBuffer_Pawn::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Pawn* pInstance = new CVIBuffer_Pawn(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CVIBuffer_Pawn"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CVIBuffer_Pawn::Clone(void* pArg)
{
	CVIBuffer_Pawn* pInstance = new CVIBuffer_Pawn(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CVIBuffer_Pawn"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Pawn::Free()
{
	__super::Free();
}
