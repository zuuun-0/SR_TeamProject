#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CTransform;
class CVIBuffer_King;
END

BEGIN(Client)

class CKing final : public CGameObject
{
public:
	CKing(LPDIRECT3DDEVICE9 pGraphic_Device);
	CKing(const CKing& Prototype);
	virtual ~CKing() = default;
public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:

	/* ��������� ������� ������? */
	CTexture* m_pTextureCom = { nullptr };
	CVIBuffer_King* m_pVIBufferCom = { nullptr };
	CTransform* m_pTransformCom = { nullptr };

private: /* �� ��ü���� �ʿ��� ������Ʈ���� �����Ͽ� �߰����ִ� ���. */
	HRESULT Ready_Components();

	void SetUp_RenderState();
	void Reset_RenderState();


public:
	static CKing* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END