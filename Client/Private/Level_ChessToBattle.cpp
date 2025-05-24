#include "Level_ChessToBattle.h"


CLevel_ChessToBattle::CLevel_ChessToBattle(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel{ pGraphic_Device }
{

}

HRESULT CLevel_ChessToBattle::Initialize()
{
	return S_OK;
}

void CLevel_ChessToBattle::Update(_float fTimeDelta)
{
	if (m_pInput_Manager->Key_Down(VK_RETURN))		// 로딩 조건 끝나면 Battle 레벨 불러오기 -- 임시로 엔터
	{
		if (FAILED(m_pGameInstance->Open_Level(ENUM_CLASS(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_BATTLE))))
			return;
	}

	else if (m_pInput_Manager->Key_Down('P'))		// 임시 -- Battle 레벨로
	{
		if (FAILED(m_pGameInstance->Open_Level(ENUM_CLASS(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_MAINMENU))))
			return;
	}
}

HRESULT CLevel_ChessToBattle::Render()
{
	SetWindowText(g_hWnd, TEXT("체스 -> 배틀 전환 레벨입니다."));

	return S_OK;
}

HRESULT CLevel_ChessToBattle::Ready_Layer(const _wstring& strLayerTag)
{
	// 변경 후 채우기

	return S_OK;
}

CLevel_ChessToBattle* CLevel_ChessToBattle::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_ChessToBattle* pInstance = new CLevel_ChessToBattle(pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed to Created : CLevel_ChessToBattle"));
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CLevel_ChessToBattle::Free()
{
	__super::Free();



}
