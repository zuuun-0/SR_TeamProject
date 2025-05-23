#pragma once
#include "Server_PCH.h"

#include "Engine_Defines.h"

#include <process.h>

#include "Client_Defines.h"

#include "BackGround.h"
#include "Bishop.h"
#include "CBullet.h"
#include "Queen.h"
#include "Camera.h"
#include "ChessBoard.h"
#include "Level_GamePlay.h"
#include "Level_Loading.h"
#include "Level_Logo.h"
#include "Loader.h"
#include "MainApp.h"
#include "Pawn.h"
#include "Player.h"
#include "Rook.h"
#include "Knight.h"
#include "King.h"
#include "TargetCamera.h"
#include "Terrain.h"

extern HWND g_hWnd;

extern CQueen* g_pClientPlayer;
extern CQueen* g_pServerPlayer;
extern SOCKET g_Socket;
extern sockaddr_in g_ServerAddr;
