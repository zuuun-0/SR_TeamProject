#include "Input_Manager.h"

IMPLEMENT_SINGLETON(CInput_Manager)

CInput_Manager::CInput_Manager()
{}

_bool CInput_Manager::Key_Pressing(_uint _iKey) const
{
	return m_bKeyState[_iKey];
}

_bool CInput_Manager::Key_Down(_uint _iKey) const
{
	return m_bKeyState[_iKey] && !m_bPrevKey[_iKey];
}

_bool CInput_Manager::Key_Up(_uint _iKey) const
{
	return !m_bKeyState[_iKey] && m_bPrevKey[_iKey];
}

void CInput_Manager::Input_Update()
{
	memcpy(&m_bPrevKey, m_bKeyState, sizeof(m_bPrevKey));
	for(int i = 0; i < VK_MAX; ++i)
	{
		m_bKeyState[i] = (GetAsyncKeyState(i) & 0x8000);
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
