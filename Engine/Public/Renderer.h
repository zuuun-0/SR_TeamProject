#pragma once

#include "Base.h"

/* �߰��ϴ� ���. */
/* ȭ�鿡 �׷��� ��ü���� �׸��� ������� �з��Ͽ� ������ Ŭ���� */
/* ������ ������� ���b���� �������� ���ش�. */

BEGIN(Engine)

class CRenderer final : public CBase
{
private:
	CRenderer(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CRenderer() = default;

public:
	HRESULT Add_RenderGroup(RENDERGROUP eRenderGroup, class CGameObject* pRenderObject);
	HRESULT Draw();

private:
	LPDIRECT3DDEVICE9						m_pGraphic_Device = {};
	list<class CGameObject*>				m_RenderObjects[ENUM_CLASS(RENDERGROUP::RG_END)];

private:
	HRESULT Render_Priority();
	HRESULT Render_NonBlend();
	HRESULT Render_Blend();
	HRESULT Render_UI();


public:
	static CRenderer* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;

};

END