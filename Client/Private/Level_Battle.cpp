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
	if (m_pInput_Manager->Key_Down(VK_RETURN))		// ���� �� -> ��� �� FPS���� �º� ���� �� Chess ���� �� �̵�  -- �ӽ÷� ����
	{
		if (FAILED(m_pGameInstance->Open_Level(ENUM_CLASS(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_CHESS))))
			return;
	}
	else if (m_pInput_Manager->Key_Down('P'))		// �ӽ� -- Chess ������
	{
		if (FAILED(m_pGameInstance->Open_Level(ENUM_CLASS(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_CHESS))))
			return;
	}
}

HRESULT CLevel_Battle::Render()
{
	SetWindowText(g_hWnd, TEXT("ü�� ��Ʋ �����Դϴ�."));

	return S_OK;
}

HRESULT CLevel_Battle::Ready_Layer(const _wstring& strLayerTag)
{
	// ���� �� ä���

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
