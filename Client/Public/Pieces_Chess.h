#pragma once
#include "LandObject.h"
BEGIN(Client)

class CPieces_Chess abstract : public CGameObject
{
public:
	typedef struct tagPieceDesc : public CLandObject::LANDOBJ_DESC
	{
		_int iTemp = {};		// ����

	}PIECE_DESC;

protected:
	CPieces_Chess(LPDIRECT3DDEVICE9 pGraphic_Device);
	CPieces_Chess(const CPieces_Chess& Prototype);
	virtual ~CPieces_Chess() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

protected:
	_int m_iTemp = {};			// ����

public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END