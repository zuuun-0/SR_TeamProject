#pragma once

//#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CBackGround final : public CGameObject
{
private:
	CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBackGround(const CBackGround& Prototype);
	virtual ~CBackGround() = default;
public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;
	void SetClinetPlayer();
private:

	/* 멤버변수를 직접들고 있을때? */
	CVIBuffer_Rect* m_pVIBufferCom = { nullptr };
	CTransform* m_pTransformCom = { nullptr };
	CTexture* m_pTextureCom = { nullptr };
	bool m_bClientPlayer = false;

private: /* 이 객체에게 필요한 컴포넌트들을 복제하여 추가해주는 기능. */
	HRESULT Ready_Components();

	void SetUp_RenderState();
	void Reset_RenderState();

public:
	static CBackGround* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END