#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CTransform;
class CVIBuffer_King;
END

BEGIN(Client)

class CBD_King final : public CPieces_Chess
{
private:
	CBD_King(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBD_King(const CBD_King& Prototype);
	virtual ~CBD_King() = default;

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
	static CBD_King* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END