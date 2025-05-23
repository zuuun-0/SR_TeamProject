#pragma once

#include "LandObject.h"

BEGIN(Client)

class CPieces_FPS abstract : public CLandObject
{
public:
	typedef struct tagPieceDesc : public CLandObject::LANDOBJ_DESC
	{
		_int iHp = {};		// 예시

	}PIECE_DESC;

protected:
	CPieces_FPS(LPDIRECT3DDEVICE9 pGraphic_Device);
	CPieces_FPS(const CPieces_FPS& Prototype);
	virtual ~CPieces_FPS() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

protected:
	_int m_iHp = {};			// 예시

public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END