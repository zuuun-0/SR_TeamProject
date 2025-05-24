#include "Weapon.h"

CWeapon::CWeapon(LPDIRECT3DDEVICE9 DEVICE)
	: CGameObject(DEVICE)
{}

CWeapon::CWeapon(const CWeapon& OTHDER)
	:CGameObject(OTHDER)
	, m_Desc(OTHDER.m_Desc)
	, m_Transform(OTHDER.m_Transform)
	, m_Texture(OTHDER.m_Texture)
	, m_VIBuffer(OTHDER.m_VIBuffer)
	, m_fAttackCooldown(OTHDER.m_fAttackCooldown)
{
	Safe_AddRef(m_Transform);
	Safe_AddRef(m_Texture);
	Safe_AddRef(m_VIBuffer);

}

HRESULT CWeapon::Initialize(void* pArg)
{
	Ready_Components();
	if(pArg == nullptr) return S_OK;
	std::memcpy(&m_Desc, pArg, sizeof(WEAPON_DESC));
	m_fAttackCooldown = 1.f / m_Desc.attackRate;
	return S_OK;
}
void CWeapon::Priority_Update(_float fTimeDelta)
{}

void CWeapon::Update(_float fTimeDelta)
{
	m_fDt += fTimeDelta;
}
void CWeapon::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_NONBLEND, this);
}

//HRESULT CWeapon::Render()
//{
//	m_Transform->Bind_Matrix();
//	if(FAILED(m_Texture->Bind_Texture()))
//		return E_FAIL;
//	m_VIBuffer->Bind_Buffers();
//
//	SetUp_RenderState();
//	m_VIBuffer->Render();
//	Reset_RenderState();
//	return S_OK;
//}

bool CWeapon::CanAttack()
{
	if(m_fAttackCooldown <= m_fDt)
	{
		m_fDt = 0.f;
		return true;
	}

	return false;
}

void CWeapon::SetUp_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

}
void CWeapon::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}

void CWeapon::Free()
{
	__super::Free();

	Safe_Release(m_Texture);
	Safe_Release(m_Transform);
	Safe_Release(m_VIBuffer);
}