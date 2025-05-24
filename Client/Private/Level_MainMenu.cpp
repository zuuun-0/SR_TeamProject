#include "Level_MainMenu.h"


CLevel_MainMenu::CLevel_MainMenu(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel{ pGraphic_Device }
{}

HRESULT CLevel_MainMenu::Initialize()
{
	if (FAILED(Ready_Layer(TEXT("Layer_Camera"))))
		return E_FAIL;

	return S_OK;
}

void CLevel_MainMenu::Update(_float fTimeDelta)
{
	if (m_pInput_Manager->Key_Down(VK_RETURN))
	{
		if (FAILED(m_pGameInstance->Open_Level(ENUM_CLASS(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_GAMEPLAY))))
			return;
	}
}

HRESULT CLevel_MainMenu::Render()
{
	SetWindowText(g_hWnd, TEXT("메인 메뉴 레벨입니다."));

	return S_OK;
}

HRESULT CLevel_MainMenu::Ready_Layer(const _wstring& strLayerTag)
{
	return S_OK;
}

CLevel_MainMenu* CLevel_MainMenu::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_MainMenu* pInstance = new CLevel_MainMenu(pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed to Created : CLevel_MainMenu"));
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CLevel_MainMenu::Free()
{
	__super::Free();



}
