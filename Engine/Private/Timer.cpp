#include "Timer.h"

CTimer::CTimer()
{
}


HRESULT CTimer::Initialize()
{
	/* ���� cpuī������ ����. */
	QueryPerformanceCounter(&m_FrameTime);			// 1077
	QueryPerformanceCounter(&m_LastTime);			// 1085
	QueryPerformanceCounter(&m_FixTime);			// 1090

	/* cpu�� 1�ʿ� ī������ �� �ִ� �ִ� ����. */
	QueryPerformanceFrequency(&m_CpuTick);

	return S_OK;
}

void CTimer::Update_Timer()
{
	QueryPerformanceCounter(&m_FrameTime);			// 1500

	if (m_FrameTime.QuadPart - m_FixTime.QuadPart >= m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_FixTime = m_FrameTime;
	}

	m_fTimeDelta = (m_FrameTime.QuadPart - m_LastTime.QuadPart) / static_cast<_float>(m_CpuTick.QuadPart);

	m_LastTime = m_FrameTime;
}

CTimer* CTimer::Create()
{
	CTimer* pInstance = new CTimer();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed to Created : CTimer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTimer::Free()
{
	__super::Free();
}
