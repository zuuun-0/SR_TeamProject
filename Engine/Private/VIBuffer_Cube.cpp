#include "VIBuffer_Cube.h"

CVIBuffer_Cube::CVIBuffer_Cube(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer{ pGraphic_Device }
{}

CVIBuffer_Cube::CVIBuffer_Cube(const CVIBuffer_Cube& Prototype)
	: CVIBuffer{ Prototype }
{}

HRESULT CVIBuffer_Cube::Initialize_Prototype()
{
	m_iNumVertices = 8;
	m_iVertexStride = sizeof(VTXCUBETEX);
	m_iFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = 12;

	m_iIndexStride = 2;
	m_iNumIndices = 36;
	m_eIndexFormat = D3DFMT_INDEX16;

#pragma region VERTEX_BUFFER
	if(FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iVertexStride * m_iNumVertices, 0, m_iFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;

	VTXCUBETEX* pVertices = { nullptr };

	m_pVB->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);

	pVertices[0].vPosition = pVertices[0].vTexcoord = _float3(-1.f, 1.f, -1.f);
	pVertices[1].vPosition = pVertices[1].vTexcoord = _float3(1.f, 1.f, -1.f);
	pVertices[2].vPosition = pVertices[2].vTexcoord = _float3(1.f, -1.f, -1.f);
	pVertices[3].vPosition = pVertices[3].vTexcoord = _float3(-1.f, -1.f, -1.f);
	pVertices[4].vPosition = pVertices[4].vTexcoord = _float3(-1.f, 1.f, 1.f);
	pVertices[5].vPosition = pVertices[5].vTexcoord = _float3(1.f, 1.f, 1.f);
	pVertices[6].vPosition = pVertices[6].vTexcoord = _float3(1.f, -1.f, 1.f);
	pVertices[7].vPosition = pVertices[7].vTexcoord = _float3(-1.f, -1.f, 1.f);

	m_pVB->Unlock();
#pragma endregion


#pragma region INDEX_BUFFER
	if(FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iIndexStride * m_iNumIndices, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
		return E_FAIL;

	_ushort* pIndices = { nullptr };

	m_pIB->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);

	// -Z
	pIndices[0] = 0;
	pIndices[1] = 1;
	pIndices[2] = 2;

	pIndices[3] = 0;
	pIndices[4] = 2;
	pIndices[5] = 3;
	
	//+Z
	pIndices[6] = 5;
	pIndices[7] = 4;
	pIndices[8] = 7;

	pIndices[9] = 5;
	pIndices[10] = 7;
	pIndices[11] = 6;

	// -X
	pIndices[12] = 4;
	pIndices[13] = 0;
	pIndices[14] = 3;

	pIndices[15] = 4;
	pIndices[16] = 3;
	pIndices[17] = 7;
	
	// +X
	pIndices[18] = 1;
	pIndices[19] = 5;
	pIndices[20] = 6;

	pIndices[21] = 1;
	pIndices[22] = 6;
	pIndices[23] = 2;
	
	// -Y
	pIndices[24] = 3;
	pIndices[25] = 2;
	pIndices[26] = 6;

	pIndices[27] = 3;
	pIndices[28] = 6;
	pIndices[29] = 7;
	
	// +Y
	pIndices[30] = 4;
	pIndices[31] = 5;
	pIndices[32] = 1;

	pIndices[33] = 4;
	pIndices[34] = 1;
	pIndices[35] = 0;

	m_pIB->Unlock();
#pragma endregion

	return S_OK;
}

HRESULT CVIBuffer_Cube::Initialize(void* pArg)
{
	return S_OK;
}

CVIBuffer_Cube* CVIBuffer_Cube::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Cube* pInstance = new CVIBuffer_Cube(pGraphic_Device);

	if(FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CVIBuffer_Cube"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CVIBuffer_Cube::Clone(void* pArg)
{
	CVIBuffer_Cube* pInstance = new CVIBuffer_Cube(*this);

	if(FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CVIBuffer_Cube"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Cube::Free()
{
	__super::Free();
}
