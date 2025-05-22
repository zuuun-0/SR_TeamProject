#pragma once
#include "Engine_Macro.h"
#include "VIBuffer.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer_Bishop : public CVIBuffer
{
public:
	CVIBuffer_Bishop(LPDIRECT3DDEVICE9 DEVICE);
	CVIBuffer_Bishop(const CVIBuffer_Bishop& OTHDER);

public:
	HRESULT Initialize_Prototype() override;
	HRESULT Initialize(void* pArg) override;
public:
	static CVIBuffer_Bishop* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;

private:
	_uint m_iRow = 0;
	_uint m_iCol = 0;
};
END