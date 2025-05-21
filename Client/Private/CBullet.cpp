#include "CBullet.h"


CBullet::CBullet(LPDIRECT3DDEVICE9 DEVICE)
	: CGameObject(DEVICE)
{}

CBullet::CBullet(const CBullet& OTHDER)
	:CGameObject(OTHDER)
{}

HRESULT CBullet::Initialize_Prototype()
{
	return S_OK;
}
HRESULT CBullet::Initialize(void* pArg)
{
	Ready_Components();
	if(pArg == nullptr) return S_OK;
	std::memcpy(&m_BulletDesc, pArg, sizeof(m_BulletDesc));
	m_Transform->Set_State(STATE::POSITION, m_BulletDesc.tf->Get_State(STATE::POSITION));
	return S_OK;
}
void CBullet::Priority_Update(_float fTimeDelta)
{}
void CBullet::Update(_float fTimeDelta)
{
	auto pos = m_Transform->Get_State(STATE::POSITION);
	pos += m_BulletDesc.dir * fTimeDelta * m_BulletDesc.speed;
	m_Transform->Set_State(STATE::POSITION, pos);
}
void CBullet::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_PRIORITY, this);
}

HRESULT CBullet::Render()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_Transform->Bind_Matrix();

	if(FAILED(m_Texture->Bind_Texture()))
		return E_FAIL;

	/* 그리기위해 이용할 자원과 설정들을 장치에 바인딩한다. */
	m_VIBuffer->Bind_Buffers();

	m_VIBuffer->Render();
	return S_OK;
}

CBullet* CBullet::Create(LPDIRECT3DDEVICE9 DEVICE)
{
	auto* newObj = new CBullet(DEVICE);
	if(FAILED((newObj->Initialize_Prototype())))
	{
		assert(false);
		Safe_Release(newObj);
	}
	return newObj;
}

HRESULT CBullet::Ready_Components()
{
	if(FAILED(Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Cube"), TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_VIBuffer))))
		return E_FAIL;

	if(FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_Component_Texture_Bullet"),
									 TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_Texture))))
		return E_FAIL;

	if(FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
									 TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_Transform))))
		return E_FAIL;

	return S_OK;
}

CGameObject* CBullet::Clone(void* pArg)
{
	auto* newObj = new CBullet(*this);
	if(FAILED(newObj->Initialize(pArg)))
	{
		assert(false);
		Safe_Release(newObj);
	}
	return newObj;
}

void CBullet::Free()
{
	__super::Free();

	Safe_Release(m_Texture);
	Safe_Release(m_Transform);
	Safe_Release(m_VIBuffer);
}
