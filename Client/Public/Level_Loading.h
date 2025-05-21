#pragma once

#include "Level.h"


/* 실제 내가 보여주고자 하는 레벨을 준비해주기위한 레벨 클래스 */
/* 로딩 -> 로고 */
/* 로딩 -> 게임플레이 */

/* 로고, 게임플레이 -> 객체, 리소스들, 사운드, 쉐이더 ->자원준비를 거치는 과정 => 로딩을 하기위한
로더객체를 생성해준다ㅣ. */

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