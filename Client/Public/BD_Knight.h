#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CTransform;
class CVIBuffer_Knight;
END

BEGIN(Client)

class CBD_Knight final : public CPieces_Chess
{
private:
	CBD_Knight(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBD_Knight(const CBD_Knight& Prototype);
	virtual ~CBD_Knight() = default;
public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:

	/* 멤버변수를 직접들고 있을때? */
	CTexture* m_pTextureCom = { nullptr };
	CVIBuffer_Knight* m_pVIBufferCom = { nullptr };
	CTransform* m_pTransformCom = { nullptr };

	bool		m_bWire;

private: /* 이 객체에게 필요한 컴포넌트들을 복제하여 추가해주는 기능. */
	HRESULT Ready_Components();

	void SetUp_RenderState();
	void Reset_RenderState();


public:
	static CBD_Knight* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END