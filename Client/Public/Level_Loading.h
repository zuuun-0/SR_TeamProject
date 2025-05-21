#pragma once

#include "Level.h"


/* ���� ���� �����ְ��� �ϴ� ������ �غ����ֱ����� ���� Ŭ���� */
/* �ε� -> �ΰ� */
/* �ε� -> �����÷��� */

/* �ΰ�, �����÷��� -> ��ü, ���ҽ���, ����, ���̴� ->�ڿ��غ� ��ġ�� ���� => �ε��� �ϱ�����
�δ���ü�� �������ش٤�. */

BEGIN(Client)

class CLevel_Loading final : public CLevel
{
private:
	CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_Loading() = default;

public:
	virtual HRESULT Initialize(LEVEL eNextLevelID);
	virtual void Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	LEVEL				m_eNextLevelID = { LEVEL::LEVEL_END };
	class CLoader*		m_pLoader = { nullptr };

private:
	HRESULT Ready_GameObjects();
	HRESULT Ready_LoadingThread();

public:
	static CLevel_Loading* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevelID);
	virtual void Free() override;
};

END