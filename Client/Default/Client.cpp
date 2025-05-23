﻿// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "Client.h"
#include "framework.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;

#pragma region Server
USING(Server);
SOCKET g_Socket;
sockaddr_in g_ServerAddr;
CPieces_FPS* g_ClientPlayer;
CPieces_FPS* g_ServerPlayer;


#pragma endregion

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

void RecvLoop();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					  _In_opt_ HINSTANCE hPrevInstance,
					  _In_ LPWSTR    lpCmdLine,
					  _In_ int       nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG


	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if(!InitInstance(hInstance, nCmdShow))
		return FALSE;

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	MSG msg;
	msg.message = WM_NULL;

	CMainApp* pMainApp = CMainApp::Create();

	if(nullptr == pMainApp)
		return FALSE;

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	CInput_Manager* pInput_Manager = CInput_Manager::GetInstance();

	Safe_AddRef(pGameInstance);
	Safe_AddRef(pInput_Manager);

	if(FAILED(pGameInstance->Add_Timer(TEXT("Timer_Default"))))
		return E_FAIL;
	if(FAILED(pGameInstance->Add_Timer(TEXT("Timer_60"))))
		return E_FAIL;

	_float fTimeAcc = {};

	// 기본 메시지 루프입니다:
	while(true)
	{
		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if(WM_QUIT == msg.message)
				break;

			if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		//if(pGameInstance->Get_Current_LevelID() == ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY))
		//	thread(RecvLoop).detach();

		pGameInstance->Compute_TimeDelta(TEXT("Timer_Default"));

		fTimeAcc += pGameInstance->Get_TimeDelta(TEXT("Timer_Default"));

		if(fTimeAcc >= (1.f / 60.f))
		{
			pGameInstance->Compute_TimeDelta(TEXT("Timer_60"));

			pMainApp->Update(pGameInstance->Get_TimeDelta(TEXT("Timer_60")));

			if(FAILED(pMainApp->Render()))
				break;

			fTimeAcc = 0.f;
		}
	}

	Safe_Release(pInput_Manager);
	Safe_Release(pGameInstance);
	Safe_Release(pMainApp);

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName   = NULL;         // 메뉴 바 삭제
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//  주석: 이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	RECT rcWindow = { 0, 0, g_iWinSizeX, g_iWinSizeY };

	AdjustWindowRect(&rcWindow, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0,
							  rcWindow.right - rcWindow.left,
							  rcWindow.bottom - rcWindow.top,
							  nullptr, nullptr, hInstance, nullptr);

	if(!hWnd)
		return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	g_hWnd = hWnd;

#pragma region SERVER
	WSADATA wsData = {};
	if(WSAStartup(MAKEWORD(2, 2), &wsData))
		return FALSE;

	g_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	g_ServerAddr.sin_family = AF_INET;
	g_ServerAddr.sin_port = htons(1530);
	inet_pton(AF_INET, "192.168.0.175", &g_ServerAddr.sin_addr);

	thread(RecvLoop).detach();
#pragma endregion


	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_KEYDOWN:
		switch(wParam)
		{
			case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// 메뉴 선택을 구문 분석합니다:
			switch(wmId)
			{
				case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
				default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_DESTROY:
		PostQuitMessage(0);
		break;
		default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void RecvLoop()
{
	char buffer[512];

	while(true)
	{
		int recvLen = recv(g_Socket, buffer, sizeof(buffer), 0);
		if(recvLen <= 0)
		{
			std::cout << "서버와 연결 끊김" << std::endl;
			break;
		}

		if(recvLen < sizeof(PACKET_HEADER))
			continue;

		PACKET_HEADER* header = reinterpret_cast<PACKET_HEADER*>(buffer);

		switch(static_cast<PACKET_TYPE>(header->ePacketType))
		{
			case PACKET_TYPE::POSITION:
			{
				POSITION_PACKET* pkt = reinterpret_cast<POSITION_PACKET*>(buffer);
				std::cout << "포지션 패킷 " << endl;
			}
			break;
			case PACKET_TYPE::ROTATION:
			{
				ROTATION_PACKET* pkt = reinterpret_cast<ROTATION_PACKET*>(buffer);
				std::cout << "회전 패킷 " << endl;

			}
			break;
			case PACKET_TYPE::FIRE:
			{
				FIRE_PACKET* pkt = reinterpret_cast<FIRE_PACKET*>(buffer);
				std::cout << "공격 패킷 " << endl;
			}
			break;
			default:
			std::cout << "알 수 없는 패킷 수신" << std::endl;
			break;
		}
	}
}

