#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Knight final : public CVIBuffer
{
private:
	CVIBuffer_Knight(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer_Knight(const CVIBuffer_Knight& Prototype);
	virtual ~CVIBuffer_Knight() = default;

public:
	HRESULT Initialize_Prototype() override;
	HRESULT Initialize(void* pArg) override;

private:
	_uint m_iRow = {};
	_uint m_iCol = {};

public:
	static CVIBuffer_Knight* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END