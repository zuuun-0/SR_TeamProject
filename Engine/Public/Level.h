#pragma once

#include "Base.h"

/* Ŭ�󰳹��ڰ� ������ ���� ����Ŭ�������� �θ� �Ǵ� Ŭ���� .*/

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