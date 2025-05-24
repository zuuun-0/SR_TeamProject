#pragma once

BEGIN(Engine)

class CRayCast final : public CBase 
{
private:
    CRayCast(LPDIRECT3DDEVICE9 pGraphic_Device);
    virtual ~CRayCast() = default;

public:
    // 마우스 위치(스크린 좌표)를 받아 Ray 생성
    HRESULT ScreenPosToRay(POINT ptMouse);

private:
    LPDIRECT3DDEVICE9 m_pGraphic_Device = { nullptr };

    _float3 vRayOrigin{}, vRayDir{};

public:
    static CRayCast* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
    virtual void Free() override;
};

END