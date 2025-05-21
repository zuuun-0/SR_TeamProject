#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Board final : public CVIBuffer
{
private:
	CVIBuffer_Board(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer_Board(const CVIBuffer_Board& Prototype);
	virtual ~CVIBuffer_Board() = default;

public:
	virtual HRESULT Initialize_Prototype(_uint iNumVerticesX, _uint iNumVerticesY);
	virtual HRESULT Initialize(void* pArg) override;

private:
	_uint m_iNumVerticesX = {};
	_uint m_iNumVerticesY = {};

	_uint m_arBoard[8][8] = {};

public:
	static CVIBuffer_Board* Create(LPDIRECT3DDEVICE9 pGraphic_Device, _uint iNumVerticesX, _uint iNumVerticesY);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END