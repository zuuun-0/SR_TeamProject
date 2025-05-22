#include "VIBuffer_Bishop.h"

CVIBuffer_Bishop::CVIBuffer_Bishop(LPDIRECT3DDEVICE9 DEVICE)
	: CVIBuffer(DEVICE)
{}

CVIBuffer_Bishop::CVIBuffer_Bishop(const CVIBuffer_Bishop& OTHDER)
	: CVIBuffer(OTHDER)
{}


HRESULT CVIBuffer_Bishop::Initialize_Prototype()
{
	struct Profile { float y, r; };
	Profile profile[] = {
		{ 0.00f, 0.55f }, // �������� �ش�
		{ 0.10f, 0.38f },
		{ 0.30f, 0.43f }, // �ణ�� ��Ǯ��
		{ 0.50f, 0.33f },
		{ 0.70f, 0.25f },
		{ 0.85f, 0.18f }, // ���� ������
		{ 0.95f, 0.12f }, // ������ �κ� ����
		{ 1.05f, 0.15f }, // ���� �����ڸ� ��¦ �о���
		{ 1.20f, 0.00f }  // ������, �����ϰ� ������
	};


	const int profileCount = sizeof(profile) / sizeof(Profile);

	const int latheSegments = 90;
	const float scaleY = 2.4f;
	const float slitAngleDeg = 45.0f; // 45�� ������ ���� Ȩ

	m_iNumVertices = profileCount * latheSegments;
	m_iVertexStride = sizeof(VTXPOSPAWN);
	m_iFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;

	m_iNumPrimitive = (profileCount - 1) * latheSegments * 2;
	m_iIndexStride = 2;
	m_iNumIndices = m_iNumPrimitive * 3;
	m_eIndexFormat = D3DFMT_INDEX16;

	if(FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iVertexStride * m_iNumVertices, 0, m_iFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;

	VTXPOSPAWN* pVertices = nullptr;
	m_pVB->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);

	for(int i = 0; i < profileCount; ++i)
	{
		for(int seg = 0; seg < latheSegments; ++seg)
		{
			float angleDeg = seg * 360.0f / latheSegments;
			float angleRad = D3DXToRadian(angleDeg);
			float y = profile[i].y * scaleY;
			float r = profile[i].r;

			if(i >= profileCount - 3) // �� �Ʒ����� ����
			{
				float x = cosf(angleRad);
				float z = sinf(angleRad);
				bool inSlit = (fabsf(x) < 0.3f || fabsf(z) < 0.3f); // ���� Ȩ ����
				if(inSlit)
					r *= 0.4f; // Ȩ �� ��� �ı�
			}


			float x = cosf(angleRad) * r;
			float z = sinf(angleRad) * r;
			pVertices[i * latheSegments + seg].vPosition = _float3(x, y, z);
		}
	}

	m_pVB->Unlock();

	if(FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iIndexStride * m_iNumIndices, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
		return E_FAIL;

	_ushort* pIndices = nullptr;
	m_pIB->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);

	int idx = 0;
	for(int i = 0; i < profileCount - 1; ++i)
	{
		for(int seg = 0; seg < latheSegments; ++seg)
		{
			int next = (seg + 1) % latheSegments;

			int a = i * latheSegments + seg;
			int b = (i + 1) * latheSegments + seg;
			int c = (i + 1) * latheSegments + next;
			int d = i * latheSegments + next;

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


HRESULT CVIBuffer_Bishop::Initialize(void* pArg)
{
	return S_OK;
}
CVIBuffer_Bishop* CVIBuffer_Bishop::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Bishop* pInstance = new CVIBuffer_Bishop(pGraphic_Device);

	if(FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : Bishop"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CVIBuffer_Bishop::Clone(void* pArg)
{
	CVIBuffer_Bishop* pInstance = new CVIBuffer_Bishop(*this);

	if(FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CBishop"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Bishop::Free()
{
	//__super::Free();
}
