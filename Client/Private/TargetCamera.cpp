#include "TargetCamera.h"

CTargetCamera::CTargetCamera(LPDIRECT3DDEVICE9 DEVICE)
	: CGameObject(DEVICE)
{}

CTargetCamera::CTargetCamera(const CTargetCamera& OTHDER)
	:CGameObject(OTHDER)
{}



HRESULT CTargetCamera::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CTargetCamera::Initialize(void* pArg)
{
	Ready_Components(nullptr);
	if(pArg == nullptr) return E_FAIL;

	std::memcpy(&m_tDesc, pArg, sizeof(m_tDesc));
	return S_OK;
}
void CTargetCamera::Priority_Update(_float fTimeDelta)
{

}
void CTargetCamera::Update(_float fTimeDelta)
{

}
void CTargetCamera::Late_Update(_float fTimeDelta)
{
	const _float3& vTargetPos = m_tDesc.target->Get_State(STATE::POSITION);
	const _float3& vTargetLook = m_tDesc.target->Get_State(STATE::LOOK);
	const _float3& vTargetRight = m_tDesc.target->Get_State(STATE::RIGHT);
	const _float3& vTargetUp = m_tDesc.target->Get_State(STATE::UP);

	_float3 normalLook;
	D3DXVec3Normalize(&normalLook, &vTargetLook);
	_float3 vCameraPos = vTargetPos - (normalLook * m_tDesc.vEye.z);
	vCameraPos.y += m_tDesc.vEye.y;

	m_pTransform->Set_State(STATE::POSITION, vCameraPos);
	m_pTransform->Set_State(STATE::RIGHT, vTargetRight);
	m_pTransform->Set_State(STATE::UP, vTargetUp);
	m_pTransform->Set_State(STATE::LOOK, vTargetLook);

	m_pGraphic_Device->SetTransform(D3DTS_VIEW, m_pTransform->Get_WorldMatrix_Inverse());

	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION,
									D3DXMatrixPerspectiveFovLH(&m_ProjMatrix,
															   m_tDesc.fFov, m_tDesc.fAspect, m_tDesc.fNear, m_tDesc.fFar));
}


HRESULT CTargetCamera::Render()
{
	return S_OK;
}

CTargetCamera* CTargetCamera::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	auto* pInstance = new CTargetCamera(pGraphic_Device);
	if(FAILED(pInstance->Initialize_Prototype()))
	{
		assert(false);
		Safe_Release(pInstance);
	}
	return pInstance;
}

HRESULT CTargetCamera::Ready_Components(void* pArg)
{
	if(FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
									 TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransform), pArg)))
		return E_FAIL;
	return S_OK;
}

CGameObject* CTargetCamera::Clone(void* pArg)
{
	auto* pInstance = new CTargetCamera(*this);
	if(FAILED(pInstance->Initialize(pArg)))
	{
		assert(false);
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTargetCamera::Free()
{
	__super::Free();
	Safe_Release(m_pTransform);
}