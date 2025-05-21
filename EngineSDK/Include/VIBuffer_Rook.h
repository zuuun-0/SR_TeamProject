#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Rook final : public CVIBuffer
{
private:
	CVIBuffer_Rook(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer_Rook(const CVIBuffer_Rook& Prototype);
	virtual ~CVIBuffer_Rook() = default;

public:
	HRESULT Initialize_Prototype() override;
	HRESULT Initialize(void* pArg) override;

private:
	_uint m_iRow = {};
	_uint m_iCol = {};

public:
	static CVIBuffer_Rook* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END