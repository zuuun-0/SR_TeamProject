#pragma once
#include "Engine_Macro.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer_Oblong : public CVIBuffer
{
private:
	CVIBuffer_Oblong(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer_Oblong(const CVIBuffer_Oblong& Prototype);
	virtual ~CVIBuffer_Oblong() = default;

public:
	HRESULT Initialize_Prototype() override;
	HRESULT Initialize(void* pArg) override;

public:
	static CVIBuffer_Oblong* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};
END
