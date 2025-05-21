#pragma once
#include "Client_Defines.h"

BEGIN(Client)
struct TARGETCAM_DESC
{
	TARGETCAM_DESC() = default;
	TARGETCAM_DESC(CTransform* TARGET, _float3 EYE, _float3 AT)
		: target(TARGET)
		, vEye(EYE), vAt(AT)
	{};

	CTransform* target = nullptr;

	_float3 vEye, vAt;
	float fFov =D3DXToRadian(60.f), fNear = 0.1f, fFar = 1000.f;
	float fAspect = static_cast<float>(g_iWinSizeX) / g_iWinSizeY;
};

class CTargetCamera : public CGameObject
{
protected:
	CTargetCamera(LPDIRECT3DDEVICE9 DEVICE);
	CTargetCamera(const CTargetCamera& OTHDER);

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Priority_Update(_float fTimeDelta);
	virtual void Update(_float fTimeDelta);
	virtual void Late_Update(_float fTimeDelta);
	virtual HRESULT Render();

	static CTargetCamera* Create(LPDIRECT3DDEVICE9 pGraphic_Device);

private:
	HRESULT Ready_Components(void* pArg);
	CGameObject* Clone(void* pArg) override;
	void Free();
private:
	CTransform* m_pTransform = nullptr;
	TARGETCAM_DESC m_tDesc;
	_float4x4 m_ProjMatrix;
};
END