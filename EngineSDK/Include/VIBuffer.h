#pragma once

#include "Component.h"

/* VIBuffer */
/* Vertex + Index + Buffer(�޸𸮰���) */
/* VIBuffer_Rect, VIBuffer_Triangle, VIBuffer_Cube, VIBuffer_Terrain */

BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer(const CVIBuffer& Prototype);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Bind_Buffers();
	virtual HRESULT Render();

public:
	

protected:
	LPDIRECT3DVERTEXBUFFER9				m_pVB = { nullptr };
	LPDIRECT3DINDEXBUFFER9				m_pIB = { nullptr };

	_uint								m_iNumVertices = { };		// ���ؽ� ����
	_uint								m_iVertexStride = { };		// �����ϳ��� ũ��(Byte)
	_uint								m_iFVF = {};				// ���ؽ� ����
	D3DPRIMITIVETYPE					m_ePrimitiveType = {};		// � Ÿ������ Ʈ���̾ޱ� �����Ұ��� ���ؼ� ���ؽ� �̱�
	_uint								m_iNumPrimitive = {};		// �ﰢ�� ����

	_uint								m_iIndexStride = {};
	_uint								m_iNumIndices = {};
	D3DFORMAT							m_eIndexFormat = {};





public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;


};

END