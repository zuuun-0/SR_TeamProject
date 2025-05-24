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
	if (m_pInput_Manager->Key_Down(VK_RETURN))		// �ε� ���� ������ Battle ���� �ҷ����� -- �ӽ÷� ����
	{
		if (FAILED(m_pGameInstance->Open_Level(ENUM_CLASS(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_BATTLE))))
			return;
	}

	else if (m_pInput_Manager->Key_Down('P'))		// �ӽ� -- Battle ������
	{
		if (FAILED(m_pGameInstance->Open_Level(ENUM_CLASS(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_MAINMENU))))
			return;
	}
}

HRESULT CLevel_ChessToBattle::Render()
{
	SetWindowText(g_hWnd, TEXT("ü�� -> ��Ʋ ��ȯ �����Դϴ�."));

	return S_OK;
}

HRESULT CLevel_ChessToBattle::Ready_Layer(const _wstring& strLayerTag)
{
	// ���� �� ä���

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
