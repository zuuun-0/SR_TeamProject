#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Pawn final : public CVIBuffer
{
private:
	CVIBuffer_Pawn(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer_Pawn(const CVIBuffer_Pawn& Prototype);
	virtual ~CVIBuffer_Pawn() = default;

public:
	HRESULT Initialize_Prototype() override;
	HRESULT Initialize(void* pArg) override;

public:
	const BOUNDINGBOX& Get_AABB() const { return m_tAABB; }

private:
	BOUNDINGBOX m_tAABB = {};

	_uint m_iRow = {};
	_uint m_iCol = {};

private:
	void ComputeAABB();

public:
	static CVIBuffer_Pawn* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END