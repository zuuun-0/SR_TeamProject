#include "Level_Chess.h"


CLevel_Chess::CLevel_Chess(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel{ pGraphic_Device }
{}

HRESULT CLevel_Chess::Initialize()
{
	if (FAILED(Ready_GameObjects()))
		return E_FAIL;

	return S_OK;
}

void CLevel_Chess::Update(_float fTimeDelta)
{
	if (m_pInput_Manager->Key_Down(VK_RETURN))		// 본인 말 -> 상대 말 Battle 시 ChessToBattle 레벨 로 이동 -- 임시로 엔터
	{
		if (FAILED(m_pGameInstance->Open_Level(ENUM_CLASS(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_CHESSTOBATTLE))))
			return;
	}

	else if (m_pInput_Manager->Key_Down('P'))		// 임시 -- 메인 메뉴 레벨로 이동
	{
		if (FAILED(m_pGameInstance->Open_Level(ENUM_CLASS(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_MAINMENU))))
			return;
	}
}

HRESULT CLevel_Chess::Render()
{
	SetWindowText(g_hWnd, TEXT("체스 플레이 레벨입니다."));

	return S_OK;
}

HRESULT CLevel_Chess::Ready_GameObjects()
{
	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_ChessBoard(TEXT("Layer_ChessBoard"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Sky(TEXT("Layer_Sky"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Pawn(TEXT("Layer_Pawn"))))
		return E_FAIL;

	// if (FAILED(Ready_Layer_Rook(TEXT("Layer_Rook"))))
	// 	return E_FAIL;

	// if (FAILED(Ready_Layer_Knight(TEXT("Layer_Knight"))))
	// 	return E_FAIL;

	// if (FAILED(Ready_Layer_Bishop(TEXT("Layer_Bishop"))))
	// 	return E_FAIL;

	// if (FAILED(Ready_Layer_Queen(TEXT("Layer_Queen"))))
	// 	return E_FAIL;

	// if (FAILED(Ready_Layer_King(TEXT("Layer_King"))))
	// 	return E_FAIL;

	return S_OK;
}

#pragma region READY_LAYERS

HRESULT CLevel_Chess::Ready_Layer_Pawn(const _wstring& strLayerTag)
{
	CBD_Pawn::PIECE_DESC PawnDesc = {};

	for (_uint i = 0; i < 8; ++i)
	{
		PawnDesc.vPosition = _float3(0.5f + i, 0.f, 1.5f);

		PawnDesc.pLandVIBuffer = static_cast<CVIBuffer*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_ChessBoard"), TEXT("Com_VIBuffer")));
		PawnDesc.pLandTransform = static_cast<CTransform*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_ChessBoard"), TEXT("Com_Transform")));

		if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
			ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_Pawn"), &PawnDesc)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_Rook(const _wstring& strLayerTag)
{
	CBD_Rook::PIECE_DESC RookDesc{};

	for (_uint i = 0; i < 2; ++i)
	{
		RookDesc.vPosition = _float3(0.5f + (i * 7.f), 0.f, 0.5f);

		RookDesc.pLandVIBuffer = static_cast<CVIBuffer*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_ChessBoard"), TEXT("Com_VIBuffer")));
		RookDesc.pLandTransform = static_cast<CTransform*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_ChessBoard"), TEXT("Com_Transform")));

		if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
			ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_Rook"), &RookDesc)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_Knight(const _wstring& strLayerTag)
{
	CBD_Knight::PIECE_DESC KnightDesc{};

	for (_uint i = 0; i < 2; ++i)
	{
		KnightDesc.vPosition = _float3(1.5f + (i * 5.f), 0.f, 0.5f);

		KnightDesc.pLandVIBuffer = static_cast<CVIBuffer*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_ChessBoard"), TEXT("Com_VIBuffer")));
		KnightDesc.pLandTransform = static_cast<CTransform*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_ChessBoard"), TEXT("Com_Transform")));

		if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
			ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_Knight"), &KnightDesc)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_Bishop(const _wstring& strLayerTag)
{
	CBD_Bishop::PIECE_DESC BishopDesc{};

	for (_uint i = 0; i < 2; ++i)
	{
		BishopDesc.vPosition = _float3(2.5f + (i * 3.f), 0.f, 0.5f);

		BishopDesc.pLandVIBuffer = static_cast<CVIBuffer*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_ChessBoard"), TEXT("Com_VIBuffer")));
		BishopDesc.pLandTransform = static_cast<CTransform*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_ChessBoard"), TEXT("Com_Transform")));

		if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
			ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_Bishop"), &BishopDesc)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_Queen(const _wstring& strLayerTag)
{
	CBD_Bishop::PIECE_DESC QueenDesc{};

	QueenDesc.vPosition = _float3(3.5f, 0.f, 0.5f);

	QueenDesc.pLandVIBuffer = static_cast<CVIBuffer*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_ChessBoard"), TEXT("Com_VIBuffer")));
	QueenDesc.pLandTransform = static_cast<CTransform*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_ChessBoard"), TEXT("Com_Transform")));

	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_Queen"), &QueenDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_King(const _wstring& strLayerTag)
{
	CBD_King::PIECE_DESC KingDesc{};

	KingDesc.vPosition = _float3(4.5f, 0.f, 0.5f);

	KingDesc.pLandVIBuffer = static_cast<CVIBuffer*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_ChessBoard"), TEXT("Com_VIBuffer")));
	KingDesc.pLandTransform = static_cast<CTransform*>(m_pGameInstance->Find_Component(ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Layer_ChessBoard"), TEXT("Com_Transform")));

	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_King"), &KingDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_Camera(const _wstring& strLayerTag)
{
	CCamera::CAMERA_DESC CameraDesc = {};

	CameraDesc.vEye = _float3(0.f, 5.f, -2.f);
	CameraDesc.vAt = _float3(0.f, 0.f, 0.f);

	CameraDesc.fFovy = D3DXToRadian(90.f);
	CameraDesc.fNear = 0.1f;
	CameraDesc.fFar = 1000.f;
	CameraDesc.fMouseSensor = 0.3f;

	CameraDesc.fSpeedPerSec = 10.f;
	CameraDesc.fRotationPerSec = D3DXToRadian(30.f);

	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_Camera"), &CameraDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Chess::Ready_Layer_Sky(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_CHESS), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_CHESS), TEXT("Prototype_GameObject_SkyForChess"))))
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

#pragma endregion

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
