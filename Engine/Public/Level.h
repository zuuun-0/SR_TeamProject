#pragma once

#include "Base.h"

/* 클라개발자가 정의한 여러 레벨클래스들의 부모가 되는 클래스 .*/

BEGIN(Engine)

class ENGINE_DLL CLevel abstract : public CBase
{
protected:
	CLevel(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel() = default;

public:
	virtual HRESULT Initialize();
	virtual void Update(_float fTimeDelta);
	virtual HRESULT Render();

protected:
	LPDIRECT3DDEVICE9		m_pGraphic_Device = { nullptr };
	class CGameInstance*	m_pGameInstance = { nullptr };
	CCollision_Manager*		m_pCollider = { nullptr };

public:	
	virtual void Free();
};

END