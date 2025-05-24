#pragma once
#include "Client_Defines.h"

BEGIN(Client)
class CBD_Bishop : public CPieces_Chess
{
private:
	CBD_Bishop(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBD_Bishop(const CBD_Bishop& Prototype);
	virtual ~CBD_Bishop() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture* m_pTextureCom = { nullptr };
	CVIBuffer_Bishop* m_pVIBufferCom = { nullptr };
	CTransform* m_pTransformCom = { nullptr };

private: /* �� ��ü���� �ʿ��� ������Ʈ���� �����Ͽ� �߰����ִ� ���. */
	HRESULT Ready_Components();

	void SetUp_RenderState();
	void Reset_RenderState();

public:
	static CBD_Bishop* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	CGameObject* Clone(void* pArg) override;
	void Free() override;
};
END