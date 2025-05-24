#pragma once

#include "Client_Defines.h"
#include "LandObject.h"

BEGIN(Engine)
class CTexture;
class CTransform;
class CVIBuffer_Pawn;
END

BEGIN(Client)

class CBD_Pawn final : public CPieces_Chess
{

private:
	CBD_Pawn(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBD_Pawn(const CBD_Pawn& Prototype);
	virtual ~CBD_Pawn() = default;
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
	CVIBuffer_Pawn* m_pVIBufferCom = { nullptr };
	CTransform* m_pTransformCom = { nullptr };

private: /* �� ��ü���� �ʿ��� ������Ʈ���� �����Ͽ� �߰����ִ� ���. */
	HRESULT Ready_Components();

	void SetUp_RenderState();
	void Reset_RenderState();

public:
	static CBD_Pawn* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END