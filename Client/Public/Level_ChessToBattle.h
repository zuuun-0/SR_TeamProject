#pragma once

#include "Level.h"

BEGIN(Client)

class CLevel_ChessToBattle final : public CLevel
{
private:
	CLevel_ChessToBattle(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_ChessToBattle() = default;

public:
	virtual HRESULT Initialize() override;
	virtual void Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	HRESULT Ready_Layer(const _wstring& strLayerTag);

public:
	static CLevel_ChessToBattle* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

END