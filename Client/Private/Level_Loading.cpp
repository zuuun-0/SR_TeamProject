#include "Level_Loading.h"


CLevel_Loading::CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel{ pGraphic_Device }
{}

HRESULT CLevel_Loading::Initialize(LEVEL eNextLevelID)
{
	m_eNextLevelID = eNextLevelID;

	/* ���� ������ �������ֱ� ���� ��ü���� �����Ѵ�. */
	if(FAILED(Ready_GameObjects()))
		return E_FAIL;

	/* ���� ������ ���� �ε��۾��� ���� �Ѵ�. */
	if(FAILED(Ready_LoadingThread()))
		return E_FAIL;

	return S_OK;
}

void CLevel_Loading::Update(_float fTimeDelta)
{
	if(true == m_pLoader->isFinished() &&
	   GetKeyState(VK_SPACE) & 0x8000)
	{
		CLevel* pNewLevel = { nullptr };

		switch(m_eNextLevelID)
		{
			case LEVEL::LEVEL_LOGO:
			pNewLevel = CLevel_Logo::Create(m_pGraphic_Device);
			break;
			case LEVEL::LEVEL_GAMEPLAY:
			pNewLevel = CLevel_GamePlay::Create(m_pGraphic_Device);
			break;
		}

		if(FAILED(m_pGameInstance->Open_Level(static_cast<_uint>(m_eNextLevelID), pNewLevel)))
			return;
	}
}

HRESULT CLevel_Loading::Render()
{
	/* �����س��� ��ü���� �����Ѵ�. */
	m_pLoader->Show_LoadingText();

	return S_OK;
}

HRESULT CLevel_Loading::Ready_GameObjects()
{
	return S_OK;
}

HRESULT CLevel_Loading::Ready_LoadingThread()
{
	m_pLoader = CLoader::Create(m_pGraphic_Device, m_eNextLevelID);
	if(nullptr == m_pLoader)
		return E_FAIL;

	return S_OK;
}

CLevel_Loading* CLevel_Loading::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevelID)
{
	CLevel_Loading* pInstance = new CLevel_Loading(pGraphic_Device);

	if(FAILED(pInstance->Initialize(eNextLevelID)))
	{
		MSG_BOX(TEXT("Failed to Created : CLevel_Loading"));
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CLevel_Loading::Free()
{
	__super::Free();

	Safe_Release(m_pLoader);

}
