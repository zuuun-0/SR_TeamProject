#pragma once

#include "Base.h"

/* ���ӿ�����Ʈ���� �θ� �Ǵ� Ŭ����. */

BEGIN(Engine)

class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device);
	CGameObject(const CGameObject& Prototype);
	virtual ~CGameObject() = default;

public:
	class CComponent* Get_Component(const _wstring& strComponentTag);

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Priority_Update(_float fTimeDelta);
	virtual void Update(_float fTimeDelta);
	virtual void Late_Update(_float fTimeDelta);
	virtual HRESULT Render();

protected:
	LPDIRECT3DDEVICE9			m_pGraphic_Device = { nullptr };
	class CGameInstance*		m_pGameInstance = { nullptr };
	class CInput_Manager*		m_pInput_Manager = { nullptr };

	map<const _wstring, class CComponent*>		m_Components;

protected:
	/*����������Ʈ�� ã�Ƽ� �����Ѵ�. */
	/*map�����̳ʿ� �����Ѵ�.  */
	/*�ڽ��� ����������� �����Ѵ�. */
	HRESULT Add_Component(_uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, 
		const _wstring& strComponentTag, CComponent** ppOut, void* pArg = nullptr);

public:	
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;

};

END