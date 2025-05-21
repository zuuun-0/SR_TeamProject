#pragma once

#include "GameObject.h"
#include "Transform.h"

BEGIN(Client)

class CCamera final : public CGameObject
{
public:
	typedef struct tagCameraDesc : CTransform::TRANSFORM_DESC
	{
		_float3 vEye{}, vAt{};
		_float fFovy{}, fNear{}, fFar{};
		_float fMouseSensor{ 1.f };

	}CAMERA_DESC;

private:
	CCamera(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCamera(const CCamera& Prototype);
	virtual ~CCamera() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTransform* m_pTransformCom = { nullptr };
	_float4x4 m_ProjMatrix = {};
	_float m_fFovy = {};
	_float m_fAspect = {};
	_float m_fNear = {};
	_float m_fFar = {};

	POINT m_OldPoint = {};
	_float m_fMouseSensor = {};

private: /* 이 객체에게 필요한 컴포넌트들을 복제하여 추가해주는 기능. */
	HRESULT Ready_Components(void* pArg);

public:
	static CCamera* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END