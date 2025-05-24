#pragma once

#include "Level.h"

BEGIN(Client)

class CLevel_Chess final : public CLevel
{
private:
	CLevel_Chess(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_Chess() = default;

public:
	virtual HRESULT Initialize() override;
	virtual void Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	HRESULT Ready_GameObjects();

	HRESULT Ready_Layer_Pawn(const _wstring& strLayerTag);
	HRESULT Ready_Layer_Rook(const _wstring& strLayerTag);
	HRESULT Ready_Layer_Knight(const _wstring& strLayerTag);
	HRESULT Ready_Layer_Bishop(const _wstring& strLayerTag);
	HRESULT Ready_Layer_Queen(const _wstring& strLayerTag);
	HRESULT Ready_Layer_King(const _wstring& strLayerTag);

	HRESULT Ready_Layer_Camera(const _wstring& strLayerTag);
	HRESULT Ready_Layer_Sky(const _wstring& strLayerTag);
	HRESULT Ready_Layer_ChessBoard(const _wstring& strLayerTag);

public:
	static CLevel_Chess* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

END