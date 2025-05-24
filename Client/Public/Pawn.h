#pragma once

#include "Client_Defines.h"
#include "LandObject.h"
#include "Weapon.h"

BEGIN(Engine)
class CTexture;
class CTransform;
class CVIBuffer_Pawn;
END

BEGIN(Client)

class CPawn final : public CPieces_FPS
{
private:
	CPawn(LPDIRECT3DDEVICE9 pGraphic_Device);
	CPawn(const CPawn& Prototype);
	virtual ~CPawn() = default;
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
	CWeapon* m_weapon = nullptr;

private: /* �� ��ü���� �ʿ��� ������Ʈ���� �����Ͽ� �߰����ִ� ���. */
	HRESULT Ready_Components();

	void SetUp_RenderState();
	void Reset_RenderState();

public:
	static CPawn* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END