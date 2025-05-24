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

	//

private:
	HRESULT Ready_Layer(const _wstring& strLayerTag);

public:
	static CLevel_Chess* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

END