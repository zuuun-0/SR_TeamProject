#include "Queen.h"

CQueen::CQueen(LPDIRECT3DDEVICE9 DEVICE)
	: CPieces_FPS(DEVICE)
{}

CQueen::CQueen(const CQueen& OTHDER)
	: CPieces_FPS(OTHDER)
{}

HRESULT CQueen::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CQueen::Initialize(void* pArg)
{
	if(FAILED(Ready_Components()))
		return E_FAIL;

	return S_OK;
}
void CQueen::Priority_Update(_float fTimeDelta)
{}


void CQueen::Update(_float fTimeDelta)
{
	if(!m_bClientPlayer) return;

	bool isMoved = false;


	if(GetKeyState(VK_SPACE) & 0x8000)
	{
		_float3 dir;
		_float3 tfDir = m_pTransformCom->Get_State(STATE::LOOK);
		D3DXVec3Normalize(&dir, &tfDir);
		CBullet::BULLET_DESC bulletDesc(m_pTransformCom, dir, 10);

		m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Layer_Bullet"),
												ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_GameObject_Bullet"), &bulletDesc);

		Server::FIRE_PACKET bulletPkt{};
		bulletPkt.header.ePacketType = Server::PACKET_TYPE::FIRE;

		bulletPkt.Pos = static_cast<CTransform*>(m_pGameInstance->Get_Object(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Layer_Bullet"))->Get_Component(TEXT("Com_Transform")))->Get_State(STATE::POSITION);

		sendto(g_Socket, reinterpret_cast<const char*>(&bulletPkt), sizeof(bulletPkt), 0, reinterpret_cast<const sockaddr*>(&g_ServerAddr), sizeof(g_ServerAddr));
	}

	if(GetKeyState('W') & 0x8000)
		m_pTransformCom->Go_Straight(fTimeDelta);

	if(GetKeyState('S') & 0x8000)
		m_pTransformCom->Go_Backward(fTimeDelta);
	if(GetKeyState('A') & 0x8000)
	{
		m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta * -5.f);
	}

	if(GetKeyState('D') & 0x8000)
	{
		m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta * 5.f);
	}

	//m_AccDt += fTimeDelta;
	//if(m_AccDt >= 0.033f)
	//{
	//	Server::TRANSFORMPACKET tfPke;
	//	tfPke.header.ePacketType = Server::PACKET_TYPE::TRANFORM;
	//
	//	tfPke.vPosition = m_pTransformCom->Get_State(STATE::POSITION);
	//	tfPke.vRight = m_pTransformCom->Get_State(STATE::RIGHT);
	//	tfPke.vUp = m_pTransformCom->Get_State(STATE::UP);
	//	tfPke.vLook = m_pTransformCom->Get_State(STATE::LOOK);
	//	sendto(g_Socket,
	//		   reinterpret_cast<const char*>(&tfPke),
	//		   sizeof(tfPke),
	//		   0,
	//		   reinterpret_cast<const sockaddr*>(&g_ServerAddr),
	//		   sizeof(g_ServerAddr));
	//	m_AccDt = 0.f;
	//}
}


void CQueen::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_NONBLEND, this);
}

HRESULT CQueen::Render()
{
	//m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	///* 알파 테스트를 수행한다. */
	///* 현재 픽셀을 그릴때 픽셀에 알파값을 비교한다. 통과한 픽셀만 그린다. */
	////m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	///* 현재 그리려고하는 픽셀과 0의 값을 비교한다,ㅡ /.*/
	////m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 250);

	///* 위에서 비교한 결과, 내가 그릴려고하는 픽셀의 알파가 0보다 크면 통과. */
	////m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//m_pTransformCom->Bind_Matrix();

	//if(FAILED(m_pTextureCom->Bind_Texture()))
	//	return E_FAIL;

	///* 그리기위해 이용할 자원과 설정들을 장치에 바인딩한다. */
	//m_pVIBufferCom->Bind_Buffers();

	//m_pVIBufferCom->Render();
	//m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_pTransformCom->Bind_Matrix();

	//if(FAILED(m_pTextureCom->Bind_Texture()))
	//	return E_FAIL;

	/* 그리기위해 이용할 자원과 설정들을 장치에 바인딩한다. */
	m_pVIBufferCom->Bind_Buffers();

	SetUp_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();

	return S_OK;
}
void CQueen::SetClinetPlayer()
{
	m_bClientPlayer = true;
}


HRESULT CQueen::Ready_Components()
{
	if(FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Queen"),
									 TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	//if(FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_Component_Texture_Queen"),
	//								 TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
	//	return E_FAIL;

	CTransform::TRANSFORM_DESC TransformDesc{};

	TransformDesc.fSpeedPerSec = 8.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(30.f);

	if(FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
									 TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom), &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

void CQueen::SetUp_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CQueen::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

CQueen* CQueen::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CQueen* pInstance = new CQueen(pGraphic_Device);

	if(FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CQueen"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CQueen::Clone(void* pArg)
{
	auto* newObj = new CQueen(*this);
	if(FAILED(newObj->Initialize(pArg)))
	{
		assert(false);
		Safe_Release(newObj);
	}
	return newObj;
}

void CQueen::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
