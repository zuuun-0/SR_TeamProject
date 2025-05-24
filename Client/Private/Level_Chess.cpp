#include "Level_Chess.h"


CLevel_Chess::CLevel_Chess(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel{ pGraphic_Device }
{
}

HRESULT CLevel_Chess::Initialize()
{
	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_ChessBoard(TEXT("Layer_ChessBoard"))))
		return E_FAIL;

	// if(FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
	//	return E_FAIL;

	//clear
	if (FAILED(Ready_Layer_Pawn(TEXT("Layer_Pawn"))))
		return E_FAIL;

	//clear
	/*if (FAILED(Ready_Layer_Rook(TEXT("Layer_Rook"))))
		return E_FAIL;*/
	//clear
	 /*if (FAILED(Ready_Layer_Bishop(TEXT("Layer_Bishop"))))
	 	return E_FAIL;*/

	//clear
	 /*if (FAILED(Ready_Layer_Knight(TEXT("Layer_Knight"))))
	 	return E_FAIL;*/

	 /*if(FAILED(Ready_Layer_Queen(TEXT("Layer_Queen"))))
	 	return E_FAIL;*/

	//clear
	 /*if (FAILED(Ready_Layer_King(TEXT("Layer_King"))))
	 	return E_FAIL;*/

	// g_pClientPlayer = static_cast<CQueen*>(m_pGameInstance->Get_Object(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Layer_Queen")));
	// g_pClientPlayer->SetClinetPlayer();
	// if(FAILED(Ready_Layer_Queen(TEXT("Layer_QueenS"))))
	// 	return E_FAIL;
	// g_pServerPlayer = static_cast<CQueen*>(m_pGameInstance->Get_Object(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Layer_QueenS")));
	// static_cast<CTransform*>(g_pServerPlayer->Get_Component(TEXT("Com_Transform")))->Set_State(STATE::POSITION, _float3(1.f, 0.f, 0.f));


	// if(FAILED(Ready_Layer_ChessBoard(TEXT("Layer_ChessBoard"))))
	// 	return E_FAIL;
	// if(FAILED(Ready_Layer_TargetCamera(TEXT("Layer_TargetCamera"), static_cast<CTransform*>(m_pGameInstance->Get_Object(static_cast<_uint>((LEVEL::LEVEL_GAMEPLAY)), TEXT("Layer_Queen"))->Get_Component(TEXT("Com_Transform"))))))
	// 	return E_FAIL;

	return S_OK;
}

void CLevel_Chess::Update(_float fTimeDelta)
{

}

HRESULT CLevel_Chess::Render()
{
	SetWindowText(g_hWnd, TEXT("ü�������Դϴ�."));

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_Player(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_Player"))))
		return E_FAIL;

	//


	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_Pawn(const _wstring& strLayerTag)
{
	CBD_Pawn::PIECE_DESC Desc{};

	Desc.iTemp = 10;

	Desc.pLandVIBuffer = static_cast<CVIBuffer*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_Terrain"), TEXT("Com_VIBuffer")));
	Desc.pLandTransform = static_cast<CTransform*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_Terrain"), TEXT("Com_Transform")));

	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_Pawn"), &Desc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_Rook(const _wstring& strLayerTag)
{
	CBD_Rook::PIECE_DESC Desc{};

	Desc.iTemp = 10;

	Desc.pLandVIBuffer = static_cast<CVIBuffer*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_Terrain"), TEXT("Com_VIBuffer")));
	Desc.pLandTransform = static_cast<CTransform*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_Terrain"), TEXT("Com_Transform")));
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_Rook"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_Knight(const _wstring& strLayerTag)
{
	CBD_Knight::PIECE_DESC Desc{};

	Desc.iTemp = 10;

	Desc.pLandVIBuffer = static_cast<CVIBuffer*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_Terrain"), TEXT("Com_VIBuffer")));
	Desc.pLandTransform = static_cast<CTransform*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_Terrain"), TEXT("Com_Transform")));
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_Knight"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_King(const _wstring& strLayerTag)
{
	CBD_King::PIECE_DESC Desc{};

	Desc.iTemp = 10;

	Desc.pLandVIBuffer = static_cast<CVIBuffer*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_Terrain"), TEXT("Com_VIBuffer")));
	Desc.pLandTransform = static_cast<CTransform*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_Terrain"), TEXT("Com_Transform")));
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_King"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_Queen(const _wstring& strLayerTag)
{
	CBD_Queen::PIECE_DESC Desc{};

	Desc.iTemp = 10;

	Desc.pLandVIBuffer = static_cast<CVIBuffer*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_Terrain"), TEXT("Com_VIBuffer")));
	Desc.pLandTransform = static_cast<CTransform*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_Terrain"), TEXT("Com_Transform")));
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_Queen"))))
		return E_FAIL;


	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_Bishop(const _wstring& strLayerTag)
{
	CBD_Bishop::PIECE_DESC Desc{};

	Desc.iTemp = 10;

	Desc.pLandVIBuffer = static_cast<CVIBuffer*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_Terrain"), TEXT("Com_VIBuffer")));
	Desc.pLandTransform = static_cast<CTransform*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_Terrain"), TEXT("Com_Transform")));
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_Bishop"))))
		return E_FAIL;


	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_Camera(const _wstring& strLayerTag)
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

	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_Camera"), &CameraDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_TargetCamera(const _wstring& strLayerTag, CTransform* Target)
{
	TARGETCAM_DESC camDesc(Target, _float3(0.f, 5.f, 10.f), Target->Get_State(STATE::POSITION));
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_TargetCamera"), &camDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_Terrain(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_Terrain"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_ChessBoard(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_ChessBoard"))))
		return E_FAIL;

	return S_OK;
}

CLevel_Chess* CLevel_Chess::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_Chess* pInstance = new CLevel_Chess(pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed to Created : CLevel_Chess"));
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CLevel_Chess::Free()
{
	__super::Free();



}
