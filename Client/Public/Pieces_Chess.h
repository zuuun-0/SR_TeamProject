#pragma once

BEGIN(Client)

class CPieces_Chess abstract : public CLandObject
{
public:
	typedef struct tagPieceDesc : public CLandObject::LANDOBJ_DESC
	{
		_float3 vPosition{};

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

public:
	void SetUp_OnChessBoard(class CTransform* pTransformCom);

public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END