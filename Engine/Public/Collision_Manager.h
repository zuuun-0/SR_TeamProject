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


#pragma region RAY_CASTING

public:
	const CRayCast* Ray() const { return m_pRayCast; }
	// 마우스 위치(스크린 좌표)를 받아 Ray 생성
	HRESULT ScreenPosToRay(POINT ptMouse);

#pragma endregion

private:
	CRayCast* m_pRayCast = { nullptr };

public:
	void Release_Collision();
	virtual void Free() override;
};

END