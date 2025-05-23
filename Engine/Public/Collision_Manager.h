#pragma once

#include "RayCast.h"

BEGIN(Engine)

class ENGINE_DLL CCollision_Manager : public CBase
{
	DECLARE_SINGLETON(CCollision_Manager)

private:
	CCollision_Manager();
	virtual ~CCollision_Manager() = default;

public:
	HRESULT Initialize(LPDIRECT3DDEVICE9 pGraphic_Device);

public:
	CRayCast* RayPicking() { return m_pRayCast; }

private:
	CRayCast* m_pRayCast = { nullptr };

public:
	void Release_Collision();
	virtual void Free() override;
};

END