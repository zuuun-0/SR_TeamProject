#include "VIBuffer_Terrain.h"

CVIBuffer_Terrain::CVIBuffer_Terrain(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer { pGraphic_Device }
{
}

CVIBuffer_Terrain::CVIBuffer_Terrain(const CVIBuffer_Terrain& Prototype)
	: CVIBuffer { Prototype }
	, m_iNumVerticesX { Prototype.m_iNumVerticesX }
	, m_iNumVerticesZ { Prototype.m_iNumVerticesZ }
{
}

HRESULT CVIBuffer_Terrain::Initialize_Prototype(_uint iNumVerticesX, _uint iNumVerticesZ)
{
	m_iNumVerticesX = iNumVerticesX;
	m_iNumVerticesZ = iNumVerticesZ;

	m_iNumVertices = m_iNumVerticesX * m_iNumVerticesZ;
	m_iVertexStride = sizeof(VTXPOSTEX);
	m_iFVF = D3DFVF_XYZ | D3DFVF_TEX1;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = (m_iNumVerticesX * m_iNumVerticesZ) * 2;

	m_iNumIndices = m_iNumPrimitive * 3;
	m_iIndexStride = 4;
	m_eIndexFormat = D3DFMT_INDEX32;

	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iNumVertices * m_iVertexStride, 0, m_iFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;

	VTXPOSTEX* pVertices = { nullptr };

	m_pVB->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);

	for (_uint i = 0; i < m_iNumVerticesZ; i++)
	{
		for (_uint j = 0; j < m_iNumVerticesX; j++)
		{
			_uint iIndex = i * m_iNumVerticesX + j;

			pVertices[iIndex].vPosition = _float3(_float(j), 0.f, _float(i));
			pVertices[iIndex].vTexcoord = _float2(static_cast<_float>(j) / m_iNumVerticesX * 10.f, static_cast<_float>(i) / m_iNumVerticesZ * 10.f);
		}
	}

	m_pVB->Unlock();
	
	
#pragma region INDEX_BUFFER
	if (FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iNumIndices * m_iIndexStride, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
		return E_FAIL;

	_uint* pIndices = { nullptr };

	_uint iCnt = { 0 };

	m_pIB->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);

	for (_uint i = 0; i < m_iNumVerticesZ - 1; i++)
	{
		for (_uint j = 0; j < m_iNumVerticesX - 1; j++)
		{
			// X 버텍스 100개, Y 버텍스 100개
			_uint iIndex = (i * m_iNumVerticesX) + j;

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
		}
	}

	m_pIB->Unlock();
#pragma endregion

	return S_OK;
}

HRESULT CVIBuffer_Terrain::Initialize_Prototype(const _tchar* pHeightMapFilePath)
{
#pragma region HEIGHT_MAP_HANDLE

	BITMAPFILEHEADER	fh = {};
	BITMAPINFOHEADER	ih = {};

	_ulong				dwByte = {};

	HANDLE hFile = CreateFile(pHeightMapFilePath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	ReadFile(hFile, &fh, sizeof(fh), &dwByte, nullptr);		// File Header

	ReadFile(hFile, &ih, sizeof(ih), &dwByte, nullptr);		// Info Header

	m_iNumVerticesX = ih.biWidth;
	m_iNumVerticesZ = ih.biHeight;

	_uint* pPixels = new _uint[m_iNumVerticesX * m_iNumVerticesZ];
	ZeroMemory(pPixels, sizeof(_uint) * m_iNumVerticesX * m_iNumVerticesZ);

	ReadFile(hFile, pPixels, sizeof(_uint) * m_iNumVerticesX * m_iNumVerticesZ, &dwByte, nullptr);

	CloseHandle(hFile);

#pragma endregion

	m_iNumVertices = m_iNumVerticesX * m_iNumVerticesZ;
	m_iVertexStride = sizeof(VTXPOSTEX);
	m_iFVF = D3DFVF_XYZ | D3DFVF_TEX1;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = ((m_iNumVerticesX - 1) * (m_iNumVerticesZ - 1)) * 2;

	m_iNumIndices = m_iNumPrimitive * 3;
	m_iIndexStride = 4;
	m_eIndexFormat = D3DFMT_INDEX32;

#pragma region VERTEX_BUFFER
	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iNumVertices * m_iVertexStride, 0, m_iFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;

	VTXPOSTEX* pVertices = { nullptr };

	m_pVertexPositions = new _float3[m_iNumVertices];
	ZeroMemory(m_pVertexPositions, sizeof(_float3) * m_iNumVertices);

	m_pVB->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);

	for (_uint i = 0; i < m_iNumVerticesZ; i++)
	{
		for (_uint j = 0; j < m_iNumVerticesX; j++)
		{
			_uint iIndex = i * m_iNumVerticesX + j;

			pVertices[iIndex].vPosition = m_pVertexPositions[iIndex] = _float3(_float(j), (pPixels[iIndex] & 0x000000ff) / 15.f, _float(i));

			_float pDest = pVertices[iIndex].vPosition.y;
			pVertices[iIndex].vTexcoord = _float2(_float(j) / (m_iNumVerticesX - 1.f) * 10.f, _float(i) / (m_iNumVerticesZ - 1) * 10.f);
		}
	}

	delete[] pPixels;
	pPixels = nullptr;

	m_pVB->Unlock();
#pragma endregion


#pragma region INDEX_BUFFER
	if (FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iNumIndices * m_iIndexStride, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
		return E_FAIL;

	_uint* pIndices = { nullptr };

	_uint iCnt = { 0 };

	m_pIB->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);

	for (_uint i = 0; i < m_iNumVerticesZ - 1; i++)
	{
		for (_uint j = 0; j < m_iNumVerticesX - 1; j++)
		{
			// X 버텍스 100개, Y 버텍스 100개
			_uint iIndex = (i * m_iNumVerticesX) + j;

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
		}
	}

	m_pIB->Unlock();
#pragma endregion

	return S_OK;
}

HRESULT CVIBuffer_Terrain::Initialize(void* pArg)
{
	return S_OK;
}

_float CVIBuffer_Terrain::Compute_Height(const _float3& vLocalPos)
{
	_uint			iIndex = static_cast<_uint>(vLocalPos.z) * m_iNumVerticesX + static_cast<_uint>(vLocalPos.x);

	_uint			iIndices[4] = {
		iIndex + m_iNumVerticesX,
		iIndex + m_iNumVerticesX + 1,
		iIndex + 1,
		iIndex
	};

	_float		fWidth = vLocalPos.x - m_pVertexPositions[iIndices[0]].x;
	_float		fDepth = m_pVertexPositions[iIndices[0]].z - vLocalPos.z;

	D3DXPLANE		Plane{};

	/* 우측 위 삼각형 안에 있다. */
	if (fWidth >= fDepth)
	{
		D3DXPlaneFromPoints(&Plane, &m_pVertexPositions[iIndices[0]], &m_pVertexPositions[iIndices[1]], &m_pVertexPositions[iIndices[2]]);
	}
	/* 왼쪽 하단 삼각형 안에 있다. */
	else
	{
		D3DXPlaneFromPoints(&Plane, &m_pVertexPositions[iIndices[0]], &m_pVertexPositions[iIndices[2]], &m_pVertexPositions[iIndices[3]]);
	}

	/*
	a b c d
	x ? z


	ax + by + cz + d = 0
	y = (-ax - cz - d) / b
	*/

	return (-Plane.a * vLocalPos.x - Plane.c * vLocalPos.z - Plane.d) / Plane.b;
}

CVIBuffer_Terrain* CVIBuffer_Terrain::Create(LPDIRECT3DDEVICE9 pGraphic_Device, _uint iNumVerticesX, _uint iNumVerticesZ)
{
	CVIBuffer_Terrain* pInstance = new CVIBuffer_Terrain(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype(iNumVerticesX, iNumVerticesZ)))
	{
		MSG_BOX(TEXT("Failed to Created : CVIBuffer_Terrain"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CVIBuffer_Terrain* CVIBuffer_Terrain::Create(LPDIRECT3DDEVICE9 pGraphic_Device, const _tchar* pHeightMapFilePath)
{
	CVIBuffer_Terrain* pInstance = new CVIBuffer_Terrain(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype(pHeightMapFilePath)))
	{
		MSG_BOX(TEXT("Failed to Created : CVIBuffer_Terrain"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CVIBuffer_Terrain::Clone(void* pArg)
{
	CVIBuffer_Terrain* pInstance = new CVIBuffer_Terrain(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CVIBuffer_Terrain"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Terrain::Free()
{
	__super::Free();
}
