#include "LandObject.h"
#include "VIBuffer.h"

#include "Transform.h"
#include "VIBuffer_Terrain.h"

CLandObject::CLandObject(LPDIRECT3DDEVICE9 pGraphic_Device)
    : CGameObject{ pGraphic_Device }
{
}

CLandObject::CLandObject(const CLandObject& Prototype)
    : CGameObject{ Prototype }
{
}

HRESULT CLandObject::Initialize_Prototype()
{
    return S_OK;
}

HRESULT CLandObject::Initialize(void* pArg)
{
    if (nullptr == pArg)
        return E_FAIL;

    LANDOBJ_DESC* pDesc = static_cast<LANDOBJ_DESC*>(pArg);

    m_pLandVIBuffer = pDesc->pLandVIBuffer;
    m_pLandTransform = pDesc->pLandTransform;

    Safe_AddRef(m_pLandVIBuffer);
    Safe_AddRef(m_pLandTransform);

    return S_OK;
}

void CLandObject::Priority_Update(_float fTimeDelta)
{
}

void CLandObject::Update(_float fTimeDelta)
{
}

void CLandObject::Late_Update(_float fTimeDelta)
{
}

HRESULT CLandObject::Render()
{
    return S_OK;
}


void CLandObject::SetUp_OnTerrain(CTransform* pTransformCom)
{
    _float3     vWorldPos = pTransformCom->Get_State(STATE::POSITION);

    _float3     vLocalPos{};
    D3DXVec3TransformCoord(&vLocalPos, &vWorldPos, m_pLandTransform->Get_WorldMatrix_Inverse());

    vLocalPos.y = dynamic_cast<CVIBuffer_Terrain*>(m_pLandVIBuffer)->Compute_Height(vLocalPos);

    D3DXVec3TransformCoord(&vWorldPos, &vLocalPos, m_pLandTransform->Get_WorldMatrix());

    pTransformCom->Set_State(STATE::POSITION, vWorldPos);
}

void CLandObject::Free()
{
    __super::Free();

    Safe_Release(m_pLandTransform);
    Safe_Release(m_pLandVIBuffer);
}
