#pragma once

#include "GameObject.h"
#include "Pieces_Chess.h"

BEGIN(Engine)
class CTexture;
class CTransform;
class CVIBuffer_Rook;
END

BEGIN(Client)

class CRook final : public CPieces_FPS
{
private:
	CRook(LPDIRECT3DDEVICE9 pGraphic_Device);
	CRook(const CRook& Prototype);
	virtual ~CRook() = default;
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
	CVIBuffer_Rook* m_pVIBufferCom = { nullptr };
	CTransform* m_pTransformCom = { nullptr };

private: /* 이 객체에게 필요한 컴포넌트들을 복제하여 추가해주는 기능. */
	HRESULT Ready_Components();

	void SetUp_RenderState();
	void Reset_RenderState();


public:
	static CRook* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END