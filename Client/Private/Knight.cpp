#include "Knight.h"

#include "GameInstance.h"

CKnight::CKnight(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject{ pGraphic_Device }
{
}

CKnight::CKnight(const CKnight& Prototype)
	: CGameObject{ Prototype }
{
}

HRESULT CKnight::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CKnight::Initialize(void* pArg)
{
	m_bWire = false;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	return S_OK;
}

void CKnight::Priority_Update(_float fTimeDelta)
{
}

void CKnight::Update(_float fTimeDelta)
{
	//m_pTransformCom->Go_Straight(fTimeDelta);
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		_float3 dir;
		_float3 tfDir = m_pTransformCom->Get_State(STATE::LOOK);
		D3DXVec3Normalize(&dir, &tfDir);
		CBullet::BULLET_DESC bulletDesc(m_pTransformCom, dir, 10);

		m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Layer_Bullet"),
			ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_GameObject_Bullet"), &bulletDesc);
	}

	if (GetKeyState('P') & 0x8000)
	{
		m_bWire = !m_bWire;
	}

	/*if (GetKeyState('W') & 0x8000)
		m_pTransformCom->Go_Straight(fTimeDelta);

	if (GetKeyState('S') & 0x8000)
		m_pTransformCom->Go_Backward(fTimeDelta);
	if (GetKeyState('A') & 0x8000)
	{
		m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta * -5.f);
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta * 5.f);
	}*/

}

void CKnight::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_PRIORITY, this);
}

HRESULT CKnight::Render()
{
	if (m_bWire)
	{
		m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	}
	else
	{
		m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	m_pTransformCom->Bind_Matrix();

	if (FAILED(m_pTextureCom->Bind_Texture()))
		return E_FAIL;

	/* 그리기위해 이용할 자원과 설정들을 장치에 바인딩한다. */
	m_pVIBufferCom->Bind_Buffers();

	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CKnight::Ready_Components()
{
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Knight"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_Component_Texture_Player"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	CTransform::TRANSFORM_DESC TransformDesc{};

	TransformDesc.fSpeedPerSec = 8.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(30.f);

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom), &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

void CKnight::SetUp_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	// m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CKnight::Reset_RenderState()
{
}

CKnight* CKnight::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CKnight* pInstance = new CKnight(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CKnight"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CKnight::Clone(void* pArg)
{
	CKnight* pInstance = new CKnight(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CKnight"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CKnight::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
