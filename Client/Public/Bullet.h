#pragma once
#include "Client_Defines.h"

BEGIN(Engine)
class CBullet : public CGameObject
{
public:
	struct BULLET_DESC
	{
		BULLET_DESC() = default;
		BULLET_DESC(CTransform* TF, _float3 DIR, float SPEED, float DAMAGE = 0.f)
			: tf(TF)
			, dir(DIR)
			, speed(SPEED)
			, damage(DAMAGE)
		{}
		CTransform* tf = nullptr;
		_float3 dir{};
		float speed = 0.f;
		float damage = 0.f;
	};

private:
	CBullet(LPDIRECT3DDEVICE9 DEVICE);
	CBullet(const CBullet& OTHDER);

private:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Priority_Update(_float fTimeDelta);
	virtual void Update(_float fTimeDelta);
	virtual void Late_Update(_float fTimeDelta);
	virtual HRESULT Render();

public:
	static CBullet* Create(LPDIRECT3DDEVICE9 DEVICE);

private:
	HRESULT Ready_Components();

	void SetUp_RenderState();
	void Reset_RenderState();

private:
	CGameObject* Clone(void* pArg) override;
	void Free() override;

private:
	CTransform* m_Transform = nullptr;
	CTexture* m_Texture = nullptr;
	CVIBuffer_Cube* m_VIBuffer = nullptr;

	BULLET_DESC m_BulletDesc;
};
END