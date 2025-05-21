#pragma once

#include "Component.h"

/* VIBuffer */
/* Vertex + Index + Buffer(메모리공간) */
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

	_uint								m_iNumVertices = { };		// 버텍스 갯수
	_uint								m_iVertexStride = { };		// 정점하나의 크기(Byte)
	_uint								m_iFVF = {};				// 버텍스 포맷
	D3DPRIMITIVETYPE					m_ePrimitiveType = {};		// 어떤 타입으로 트라이앵글 추출할건지 정해서 버텍스 뽑기
	_uint								m_iNumPrimitive = {};		// 삼각형 갯수

	_uint								m_iIndexStride = {};
	_uint								m_iNumIndices = {};
	D3DFORMAT							m_eIndexFormat = {};





public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;


};

END