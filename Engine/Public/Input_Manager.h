#pragma once

BEGIN(Engine)

class ENGINE_DLL CInput_Manager final : public CBase
{
	DECLARE_SINGLETON(CInput_Manager)

private:
	CInput_Manager();
	virtual ~CInput_Manager() = default;

public:
	_bool		Key_Pressing(_uint _iKey) const;
	_bool		Key_Down(_uint _iKey) const;
	_bool		Key_Up(_uint _iKey) const;
	void		Input_Update();

private:
	_bool		m_bKeyState[VK_MAX], m_bPrevKey[VK_MAX] = {};

public:
	void Release_Input();
	virtual void Free() override;
};

END