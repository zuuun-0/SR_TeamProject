#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_King final : public CVIBuffer
{
private:
	CVIBuffer_King(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer_King(const CVIBuffer_King& Prototype);
	virtual ~CVIBuffer_King() = default;

public:
	HRESULT Initialize_Prototype() override;
	HRESULT Initialize(void* pArg) override;

private:
	_uint m_iRow = {};
	_uint m_iCol = {};

public:
	static CVIBuffer_King* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END