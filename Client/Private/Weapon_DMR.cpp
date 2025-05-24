#include "Weapon_DMR.h"

CWeapon_DMR::CWeapon_DMR(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CWeapon(pGraphic_Device)
{}

CWeapon_DMR::CWeapon_DMR(const CWeapon_DMR& Prototype)
	: CWeapon(Prototype)
{}

void CWeapon_DMR::Attack()
{
	if(CanAttack())
	{
		_float3 dir;
		_float3 tfDir = m_Desc.transform->Get_State(STATE::LOOK);
		D3DXVec3Normalize(&dir, &tfDir);
		CBullet::BULLET_DESC bulletDesc(m_Desc.transform, dir, 10, m_Desc.damage);

		m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Layer_Bullet"),
												ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_GameObject_Bullet"), &bulletDesc);
	}
}

HRESULT CWeapon_DMR::Ready_Components()
{

	CTransform::TRANSFORM_DESC TransformDesc{};

	TransformDesc.fSpeedPerSec = 8.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(30.f);

	if(FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
									 TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_Transform), &TransformDesc)))
		return E_FAIL;



	return S_OK;
}

CWeapon_DMR* CWeapon_DMR::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CWeapon_DMR* pInstance = new CWeapon_DMR(pGraphic_Device);

	if(FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : Weapon_DMR"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CWeapon_DMR::Clone(void* pArg)
{
	auto* newObj = new CWeapon_DMR(*this);
	if(FAILED(newObj->Initialize(pArg)))
	{
		return nullptr;
	}
	return newObj;
}

HRESULT CWeapon_DMR::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CWeapon_DMR::Render()
{
	m_Transform->Bind_Matrix();
	//if(FAILED(m_Texture->Bind_Texture()))
	//	return E_FAIL;
	//m_VIBuffer->Bind_Buffers();

	SetUp_RenderState();
	//m_VIBuffer->Render();
	Reset_RenderState();
	return S_OK;
}
