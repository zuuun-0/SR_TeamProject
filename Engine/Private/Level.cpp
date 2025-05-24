#include "Level.h"

#include "GameInstance.h"

CLevel::CLevel(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device { pGraphic_Device }
	, m_pGameInstance { CGameInstance::GetInstance() }
	, m_pInput_Manager{ CInput_Manager::GetInstance() }
	, m_pCollider{ CCollision_Manager::GetInstance() }
{
	Safe_AddRef(m_pCollider);
	Safe_AddRef(m_pInput_Manager);
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CLevel::Initialize()
{
	return S_OK;
}

void CLevel::Update(_float fTimeDelta)
{
}

HRESULT CLevel::Render()
{
	return S_OK;
}

void CLevel::Free()
{
	__super::Free();

	Safe_Release(m_pCollider);
	Safe_Release(m_pInput_Manager);
	Safe_Release(m_pGameInstance);
	Safe_Release(m_pGraphic_Device);
}
