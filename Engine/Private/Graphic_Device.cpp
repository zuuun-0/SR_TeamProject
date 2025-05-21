#include "Graphic_Device.h"

CGraphic_Device::CGraphic_Device()
	: m_pSDK(nullptr)
	, m_pGraphicDev(nullptr)
{

}


HRESULT CGraphic_Device::Ready_GraphicDev(HWND hWnd, WINMODE eMode, const int iSizeX, const int iSizeY, LPDIRECT3DDEVICE9* ppOut)
{
	/* m_pSDK : LPDIRECT3DDEVICE9을 생성하기위한 사전 역활을 수행 및 LPDIRECT3DDEVICE9 생성해주는 기능을 수행한다. */
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	if(NULL == m_pSDK)
		return E_FAIL;

	D3DCAPS9		DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	/* 현재 꽂혀있는 그래픽카드의 성능 정보를 가져온다. */
	if(FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		return E_FAIL;
	}

	_ulong	dwFlag = 0;

	/* 다양한 기능들 중에 특정 기능 하나만 조사하고 있다. */
	/* VERTEXPROCESSING의 역할 수행이 가능한지를 조사한다. */
	/* VERTEXPROCESSING : Transform + Light */
	/* Transform : 정점의 변환. */
	/* Light : 빛 연산 */

	if(DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		dwFlag |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	else
		dwFlag |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	/* DirectX초기화에 필요한 데이터들을 사용자가 직접 셋팅하는 과정. */
	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	Set_Parameters(d3dpp, hWnd, eMode, iSizeX, iSizeY);

	if(FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, dwFlag, &d3dpp, &m_pGraphicDev)))
	{
		return E_FAIL;
	}

	*ppOut = m_pGraphicDev;

	Safe_AddRef(m_pGraphicDev);

	return S_OK;
}

LPDIRECT3DDEVICE9 CGraphic_Device::GetDevice() const
{
	return m_pGraphicDev;
}
// 후면 버퍼 
void CGraphic_Device::Render_Begin(D3DXCOLOR Color)
{
	m_pGraphicDev->Clear(0,		// 렉트의 개수
						 nullptr,	// 렉트의 첫 번째 주소
						 D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
						 Color,	// 백 버퍼의 색상
						 1.f,	// 깊이 버퍼 초기화 값
						 0);		// 스텐실 버퍼 초기화 값

	m_pGraphicDev->BeginScene();
	//m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

}

void CGraphic_Device::Render_End(HWND hWnd)
{
	//m_pSprite->End();
	m_pGraphicDev->EndScene();
	m_pGraphicDev->Present(nullptr, nullptr, hWnd, nullptr);
}

void CGraphic_Device::Set_Parameters(D3DPRESENT_PARAMETERS& d3dpp,
									 HWND hWnd, WINMODE eMode, const int iSizeX, const int iSizeY)
{
	/* 백버퍼를 위한 설정들. */
	/* DirectX는 WinAPI와는 다르게 스스로 백버퍼를 하나 생성하여 들고 있을 수 있게 한다. */
	d3dpp.BackBufferWidth  = iSizeX;
	d3dpp.BackBufferHeight = iSizeY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount  = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// D3DSWAPEFFECT_DISCARD : 스왑 체인을 이용한 방식
	// D3DSWAPEFFECT_FLIP    : 버퍼를 하나만 두어 앞, 뒷면을 번갈아가며 화면을 갱신하는 방식
	// D3DSWAPEFFECT_COPY    : 더블 버퍼링과 유사한 방식

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.hDeviceWindow = hWnd;

	d3dpp.Windowed = static_cast<BOOL>(eMode);

	/* 깊이 테스팅을 위한 버퍼를 어떻게 생성하고 할건지말건지? */
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	// 전체화면 모드일 때 설정
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

CGraphic_Device* CGraphic_Device::Create(HWND hWnd, WINMODE eMode, const int iSizeX, const int iSizeY, LPDIRECT3DDEVICE9* ppOut)
{
	CGraphic_Device* pInstance = new CGraphic_Device();

	if(FAILED(pInstance->Ready_GraphicDev(hWnd, eMode, iSizeX, iSizeY, ppOut)))
	{
		MSG_BOX(TEXT("Failed to Created : CGraphic_Device"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CGraphic_Device::Free()
{
	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pSDK);
}
