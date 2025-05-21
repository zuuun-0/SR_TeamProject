#pragma once

#include "Base.h"

/* ���������� ���ο� ������ ��ü���ش�. */
/* ���� �Ҵ�Ǿ��ִ� ������ ���Ű� �������� ����Ѵ�. */

/* ������Ʈ �Ŵ��� + �ڿ� �Ŵ��� => �������� �����ؼ� �����Ѵ�. */
/* ���� ��ü �ÿ� ���� ������ �ı��ϰų� ���� �������� �������ؼ� �غ��س��� �ڿ����� �����Ѵ�. */

/* �Ҵ�� ������ �����Ѵ�. */

BEGIN(Engine)

class CLevel_Manager final : public CBase
{
private:
	CLevel_Manager();
	virtual ~CLevel_Manager() = default;

public:
	HRESULT Open_Level(_uint iLevelID, class CLevel* pNewLevel);
	void Update(_float fTimeDelta);
	HRESULT Render();

public:
	_uint Get_Current_LevelID() { return m_iCurrentLevelID; }

private:
	class CLevel*				m_pCurrentLevel = { nullptr };
	class CGameInstance*		m_pGameInstance = { nullptr };
	_uint						m_iCurrentLevelID = { };

private:
	HRESULT Clear_Resources();

public:
	static CLevel_Manager* Create();
	virtual void Free() override;

};

END