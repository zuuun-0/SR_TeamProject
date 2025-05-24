#include "Level_Battle.h"


CLevel_Battle::CLevel_Battle(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel{ pGraphic_Device }
{

}

HRESULT CLevel_Battle::Initialize()
{
	return S_OK;
}

void CLevel_Battle::Update(_float fTimeDelta)
{
	if (m_pInput_Manager->Key_Down(VK_RETURN))		// 본인 말 -> 상대 말 FPS에서 승부 판정 시 Chess 레벨 로 이동  -- 임시로 엔터
	{
		if (FAILED(m_pGameInstance->Open_Level(ENUM_CLASS(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_CHESS))))
			return;
	}
	else if (m_pInput_Manager->Key_Down('P'))		// 임시 -- Chess 레벨로
	{
		if (FAILED(m_pGameInstance->Open_Level(ENUM_CLASS(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_CHESS))))
			return;
	}
}

HRESULT CLevel_Battle::Render()
{
	SetWindowText(g_hWnd, TEXT("체스 배틀 레벨입니다."));

	return S_OK;
}

HRESULT CLevel_Battle::Ready_Layer(const _wstring& strLayerTag)
{
	// 변경 후 채우기

	return S_OK;
}

CLevel_Battle* CLevel_Battle::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_Battle* pInstance = new CLevel_Battle(pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed to Created : CLevel_Battle"));
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CLevel_Battle::Free()
{
	__super::Free();



}
