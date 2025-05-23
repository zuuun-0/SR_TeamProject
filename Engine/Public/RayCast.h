#pragma once

BEGIN(Engine)

class CRayCast final : public CBase 
{
private:
    CRayCast(LPDIRECT3DDEVICE9 pGraphic_Device);
    virtual ~CRayCast() = default;

public:
    // ���콺 ��ġ(��ũ�� ��ǥ)�� �޾� Ray ����
    HRESULT ScreenPosToRay(POINT ptMouse);

private:
    LPDIRECT3DDEVICE9 m_pGraphic_Device = { nullptr };

    _float3 vRayOrigin{}, vRayDir{};

public:
    static CRayCast* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
    virtual void Free() override;
};

END