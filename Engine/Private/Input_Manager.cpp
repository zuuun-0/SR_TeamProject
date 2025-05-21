#include "Input_Manager.h"

IMPLEMENT_SINGLETON(CInput_Manager)

CInput_Manager::CInput_Manager()
{
}

_bool CInput_Manager::Key_Pressing(_uint _iKey)
{
	if (GetAsyncKeyState(_iKey) & 0x8000)
		return true;

	return false;
}

_bool CInput_Manager::Key_Down(_uint _iKey)
{
	// 이전 프레임에 눌린 적이 없고, 현재 프레임에 눌린 상태

	if ((!m_bKeyState[_iKey]) && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	return false;
}

_bool CInput_Manager::Key_Up(_uint _iKey)
{
	// 이전 프레임에 눌렸고, 현재 프레임에 누르지 않은 상태
	if ((m_bKeyState[_iKey]) && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	return false;
}

void CInput_Manager::Input_Update()
{
	for (int i = 0; i < VK_MAX; ++i)
	{
		if ((m_bKeyState[i]) && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];

		if ((!m_bKeyState[i]) && (GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}
}

void CInput_Manager::Release_Input()
{
	Release();
}

void CInput_Manager::Free()
{
	__super::Free();
}
