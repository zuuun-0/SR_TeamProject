#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_MainMenu final : public CLevel
{
private:
	CLevel_MainMenu(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_MainMenu() = default;

public:
	virtual HRESULT Initialize() override;
	virtual void Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	HRESULT Ready_Layer(const _wstring& strLayerTag);

public:
	static CLevel_MainMenu* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

END