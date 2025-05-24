#pragma once
#include "Weapon.h"

class CWeapon_DMR : public CWeapon
{
public:
	CWeapon_DMR(LPDIRECT3DDEVICE9 pGraphic_Device);
	CWeapon_DMR(const CWeapon_DMR& Prototype);


	void Attack() override;
	HRESULT Ready_Components() override;
	CGameObject* Clone(void* pArg) override;

	HRESULT Initialize_Prototype() override;
	static CWeapon_DMR* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	HRESULT Render() override;

};

