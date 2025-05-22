#include "Level_GamePlay.h"


CLevel_GamePlay::CLevel_GamePlay(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel{ pGraphic_Device }
{}

HRESULT CLevel_GamePlay::Initialize()
{
	// if(FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
	//	return E_FAIL;
	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;
	if (FAILED(Ready_Layer_Terrain(TEXT("Layer_Terrain"))))
		return E_FAIL;
	if (FAILED(Ready_Layer_Pawn(TEXT("Layer_Pawn"))))
		return E_FAIL;
	// if (FAILED(Ready_Layer_Rook(TEXT("Layer_Rook"))))
	// 	return E_FAIL;
<<<<<<< HEAD
	// if(FAILED(Ready_Layer_Queen(TEXT("Layer_Queen"))))
	// 	return E_FAIL;
	// g_pClientPlayer = static_cast<CQueen*>(m_pGameInstance->Get_Object(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Layer_Queen")));
	// g_pClientPlayer->SetClinetPlayer();
	// if(FAILED(Ready_Layer_Queen(TEXT("Layer_QueenS"))))
	// 	return E_FAIL;
	// g_pServerPlayer = static_cast<CQueen*>(m_pGameInstance->Get_Object(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Layer_QueenS")));
	// static_cast<CTransform*>(g_pServerPlayer->Get_Component(TEXT("Com_Transform")))->Set_State(STATE::POSITION, _float3(1.f, 0.f, 0.f));

=======
	if(FAILED(Ready_Layer_Rook(TEXT("Layer_Rook"))))
		return E_FAIL;
	if(FAILED(Ready_Layer_Queen(TEXT("Layer_Queen"))))
		return E_FAIL;
	g_pClientPlayer = static_cast<CQueen*>(m_pGameInstance->Get_Object(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Layer_Queen")));
	g_pClientPlayer->SetClinetPlayer();
	if(FAILED(Ready_Layer_Queen(TEXT("Layer_QueenS"))))
		return E_FAIL;
	g_pServerPlayer = static_cast<CQueen*>(m_pGameInstance->Get_Object(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Layer_QueenS")));
	static_cast<CTransform*>(g_pServerPlayer->Get_Component(TEXT("Com_Transform")))->Set_State(STATE::POSITION, _float3(1.f, 0.f, 0.f));

	if(FAILED(Ready_Layer_Bishop(TEXT("Layer_Bishop"))))
		return E_FAIL;

	// if(FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
	//	return E_FAIL;
	if(FAILED(Ready_Layer_Terrain(TEXT("Layer_Terrain"))))
		return E_FAIL;
>>>>>>> KIM
	// if(FAILED(Ready_Layer_ChessBoard(TEXT("Layer_ChessBoard"))))
	// 	return E_FAIL;
	// if(FAILED(Ready_Layer_TargetCamera(TEXT("Layer_TargetCamera"), static_cast<CTransform*>(m_pGameInstance->Get_Object(static_cast<_uint>((LEVEL::LEVEL_GAMEPLAY)), TEXT("Layer_Queen"))->Get_Component(TEXT("Com_Transform"))))))
	// 	return E_FAIL;

	return S_OK;
}

void CLevel_GamePlay::Update(_float fTimeDelta)
{

}

HRESULT CLevel_GamePlay::Render()
{
	SetWindowText(g_hWnd, TEXT("게임플레이레벨입니다."));

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Player(const _wstring& strLayerTag)
{
	if(FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), strLayerTag,
													  ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_GameObject_Player"))))
		return E_FAIL;


	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Pawn(const _wstring& strLayerTag)
{
<<<<<<< HEAD
	CPawn::PAWN_DESC Desc = {};

	Desc.iTemp = 0;
	Desc.pLandVIBuffer = static_cast<CVIBuffer*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Layer_Terrain"), TEXT("Com_VIBuffer"), 0));
	Desc.pLandTransform = static_cast<CTransform*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Layer_Terrain"), TEXT("Com_Transform"), 0));

	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_GameObject_Pawn"), &Desc)))
=======
	if(FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), strLayerTag,
													  ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_GameObject_Pawn"))))
>>>>>>> KIM
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Rook(const _wstring& strLayerTag)
{
	if(FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), strLayerTag,
													  ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_GameObject_Rook"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Queen(const _wstring& strLayerTag)
{
	if(FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), strLayerTag,
													  ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_GameObject_Queen"))))
		return E_FAIL;


	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Bishop(const _wstring& strLayerTag)
{
	if(FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), strLayerTag,
													  ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_GameObject_Bishop"))))
		return E_FAIL;
	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Camera(const _wstring& strLayerTag)
{
	CCamera::CAMERA_DESC CameraDesc = {};

	CameraDesc.vEye = _float3(0.f, 10.f, -10.f);
	CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
	CameraDesc.fFovy = D3DXToRadian(60.f);
	CameraDesc.fNear = 0.1f;
	CameraDesc.fFar = 1000.f;
	CameraDesc.fMouseSensor = 0.3f;

	CameraDesc.fSpeedPerSec = 5.f;
	CameraDesc.fRotationPerSec = D3DXToRadian(30.f);

	if(FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), strLayerTag,
													  ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_GameObject_Camera"), &CameraDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_TargetCamera(const _wstring& strLayerTag, CTransform* Target)
{
	TARGETCAM_DESC camDesc(Target, _float3(0.f, 5.f, 10.f), Target->Get_State(STATE::POSITION));
	if(FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), strLayerTag,
													  ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_GameObject_TargetCamera"), &camDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Terrain(const _wstring& strLayerTag)
{
	if(FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), strLayerTag,
													  ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_GameObject_Terrain"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_ChessBoard(const _wstring& strLayerTag)
{
	if(FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), strLayerTag,
													  ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_GameObject_ChessBoard"))))
		return E_FAIL;

	return S_OK;
}

CLevel_GamePlay* CLevel_GamePlay::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_GamePlay* pInstance = new CLevel_GamePlay(pGraphic_Device);

	if(FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed to Created : CLevel_GamePlay"));
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CLevel_GamePlay::Free()
{
	__super::Free();



}
