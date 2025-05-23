#pragma once
#include "Client_Defines.h"

BEGIN(Client)
class CQueen : public CGameObject
{
public:
	CQueen(LPDIRECT3DDEVICE9 DEVICE);
	CQueen(const CQueen& OTHDER);

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	void SetClinetPlayer();


public:
	static CQueen* Create(LPDIRECT3DDEVICE9 DEVICE);
	CGameObject* Clone(void* pArg) override;
	void Free() override;

private: /* 이 객체에게 필요한 컴포넌트들을 복제하여 추가해주는 기능. */
	HRESULT Ready_Components();

	void SetUp_RenderState();
	void Reset_RenderState();

private:
	CTexture* m_pTextureCom = { nullptr };
	CVIBuffer_Queen* m_pVIBufferCom = { nullptr };
	CTransform* m_pTransformCom = { nullptr };
	bool m_bClientPlayer = false;
	float m_AccDt = 0.f;
};
END