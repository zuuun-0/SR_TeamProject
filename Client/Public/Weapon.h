#pragma once

class CWeapon : public CGameObject
{
public:
	typedef struct tagWeaponDesc
	{
		tagWeaponDesc() = default;
		tagWeaponDesc(CTransform* Transform, float Damage, float AttackRate)
			: transform(Transform), damage(Damage), attackRate(AttackRate)
		{}
		CTransform* transform = nullptr;;
		float damage = 0.f;
		float attackRate = 0.f;
		bool canAttack = true;
	}WEAPON_DESC;

public:
	CWeapon(LPDIRECT3DDEVICE9 DEVICE);
	CWeapon(const CWeapon& OTHDER);

public:
	virtual void Attack() PURE;

protected:
	virtual HRESULT Initialize_Prototype() PURE;
	virtual HRESULT Initialize(void* pArg);
	virtual void Priority_Update(_float fTimeDelta);
	virtual void Update(_float fTimeDelta);
	virtual void Late_Update(_float fTimeDelta);
	virtual HRESULT Render() PURE;

protected:
	bool CanAttack();

private:
	virtual HRESULT Ready_Components() PURE;

protected:
	void SetUp_RenderState();
	void Reset_RenderState();

private:
	CGameObject* Clone(void* pArg) override PURE;
	void Free() override;

protected:
	CTransform* m_Transform = nullptr;
	CTexture* m_Texture = nullptr;
	CVIBuffer_Cube* m_VIBuffer = nullptr;

	WEAPON_DESC m_Desc;

	float m_fAttackCooldown = 0.f;
	float m_fDt = 0.f;
};

