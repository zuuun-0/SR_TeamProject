#pragma once

#include "Level.h"

BEGIN(Client)

class CLevel_Battle final : public CLevel
{
private:
	CLevel_Battle(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_Battle() = default;

public:
	virtual HRESULT Initialize() override;
	virtual void Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	HRESULT Ready_Layer(const _wstring& strLayerTag);

public:
	static CLevel_Battle* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

END