#include "Level_Chess.h"


CLevel_Chess::CLevel_Chess(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel{ pGraphic_Device }
{}

HRESULT CLevel_Chess::Initialize()
{
	return S_OK;
}

void CLevel_Chess::Update(_float fTimeDelta)
{
	if (m_pInput_Manager->Key_Down(VK_RETURN))		// ���� �� -> ��� �� Battle �� ChessToBattle ���� �� �̵� -- �ӽ÷� ����
	{
		if (FAILED(m_pGameInstance->Open_Level(ENUM_CLASS(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_CHESSTOBATTLE))))
			return;
	}

	else if (m_pInput_Manager->Key_Down('P'))		// �ӽ� -- ���� �޴� ������ �̵�
	{
		if (FAILED(m_pGameInstance->Open_Level(ENUM_CLASS(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_MAINMENU))))
			return;
	}
}

HRESULT CLevel_Chess::Render()
{
	SetWindowText(g_hWnd, TEXT("ü�� �÷��� �����Դϴ�."));

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer(const _wstring& strLayerTag)
{

	//


	return S_OK;
}

CLevel_Chess* CLevel_Chess::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_Chess* pInstance = new CLevel_Chess(pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed to Created : CLevel_Chess"));
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CLevel_Chess::Free()
{
	__super::Free();



}
