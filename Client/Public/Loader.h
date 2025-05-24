#pragma once

#include "Base.h"
#include "Client_Defines.h"

/* 로고, 게임플레이 -> 객체, 리소스들, 사운드, 쉐이더 ->자원준비를 거치는 과정 => 로딩 */

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Client)

class CLoader final : public CBase
{
private:
	CLoader(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLoader() = default;

	/* 세마포어 , 뮤텍스, 크리티컬섹션 */

public:
	HRESULT Initialize(LEVEL eNextLevelID);
	HRESULT Loading();

	_bool isFinished()
	{
		return m_isFinished;
	}

	void Show_LoadingText() const;

private:
	LPDIRECT3DDEVICE9				m_pGraphic_Device = { nullptr };
	LEVEL							m_eNextLevelID = { LEVEL::LEVEL_END };
	HANDLE							m_hThread = {};
	_tchar							m_szLoadingText[MAX_PATH] = {};
	_bool							m_isFinished = { false };
	CGameInstance*					m_pGameInstance = { nullptr };
	CRITICAL_SECTION				m_CriticalSection = {};



private:

	HRESULT Loading_For_Logo_Level();
	HRESULT Loading_For_MainMenu_Level();
	HRESULT Loading_For_GamePlay_Level();
	HRESULT Loading_For_Chess_Level();
	HRESULT Loading_For_ChessToBattle_Level();
	HRESULT Loading_For_Battle_Level();



public:
	static CLoader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevelID);
	virtual void Free() override;
};

END