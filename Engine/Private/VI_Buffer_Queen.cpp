#include "VI_Buffer_Queen.h"

CVIBuffer_Queen::CVIBuffer_Queen(LPDIRECT3DDEVICE9 DEVICE)
	: CVIBuffer(DEVICE)
{}

CVIBuffer_Queen::CVIBuffer_Queen(const CVIBuffer_Queen& OTHDER)
	: CVIBuffer(OTHDER)
{}

HRESULT CVIBuffer_Queen::Initialize_Prototype()
{
	VTXPOSTEX vertices[] = {
		// y = 0 ~ 10, ���� 30
		{ D3DXVECTOR3(-15, 0, 0), D3DXVECTOR2(0, 0) },  // 0
		{ D3DXVECTOR3(15, 0, 0), D3DXVECTOR2(1, 0) },  // 1
		{ D3DXVECTOR3(-15,10, 0), D3DXVECTOR2(0, 1) },  // 2
		{ D3DXVECTOR3(15,10, 0), D3DXVECTOR2(1, 1) },  // 3

		// y = 10 ~ 20, ���� 20
		{ D3DXVECTOR3(-10,10, 0), D3DXVECTOR2(0, 0) },  // 4
		{ D3DXVECTOR3(10,10, 0), D3DXVECTOR2(1, 0) },  // 5
		{ D3DXVECTOR3(-10,20, 0), D3DXVECTOR2(0, 1) },  // 6
		{ D3DXVECTOR3(10,20, 0), D3DXVECTOR2(1, 1) },  // 7

		// y = 20 ~ 30, ���� 10
		{ D3DXVECTOR3(-5,20, 0), D3DXVECTOR2(0, 0) },   // 8
		{ D3DXVECTOR3(5,20, 0), D3DXVECTOR2(1, 0) },   // 9
		{ D3DXVECTOR3(-5,30, 0), D3DXVECTOR2(0, 1) },   // 10
		{ D3DXVECTOR3(5,30, 0), D3DXVECTOR2(1, 1) },   // 11
	};
	WORD indices[] = {
		// ù �簢�� (0,1,2,3)
		0, 1, 2,
		2, 1, 3,

		// ��° �簢�� (4,5,6,7)
		4, 5, 6,
		6, 5, 7,

		// ��° �簢�� (8,9,10,11)
		8, 9,10,
		10, 9,11,
	};

	return S_OK;
}
HRESULT CVIBuffer_Queen::Render()
{
	m_pGraphic_Device->SetFVF(VTXPOSTEX::FVF);

	// ���� ���ۿ� �ε��� ���� ���� (����: ���� �Ҵ� ����)
	m_pGraphic_Device->SetStreamSource(0, m_pVB, 0, sizeof(VTXPOSTEX));
	m_pGraphic_Device->SetIndices(m_pIB);

	// �ﰢ�� 6�� -> 2���� * 3��
	m_pGraphic_Device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0,        // BaseVertexIndex
		0,        // MinVertexIndex
		12,       // NumVertices
		0,        // StartIndex
		6         // PrimitiveCount (�ﰢ�� 6��)
	);
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
	Safe_Release(m_pIB);
}