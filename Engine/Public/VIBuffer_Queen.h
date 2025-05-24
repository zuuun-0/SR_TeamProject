#pragma once
#include "Engine_Macro.h"
#include "Engine_Typedef.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer_Queen : public CVIBuffer
{
private:
	CVIBuffer_Queen(LPDIRECT3DDEVICE9 DEVICE);
	CVIBuffer_Queen(const CVIBuffer_Queen& OTHDER);

public:
	HRESULT Initialize_Prototype() override;
	HRESULT Initialize(void* pArg) override;

private:
	_uint m_iRow = {};
	_uint m_iCol = {};

public:
	static CVIBuffer_Queen* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};
END