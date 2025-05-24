#pragma once
#include "Server_PCH.h"

#include "Engine_Defines.h"

#include <process.h>

#include "Client_Defines.h"

#include "Pieces_Chess.h"
#include "Pieces_FPS.h"
#include "BackGround.h"
#include "Bishop.h"
#include "Bullet.h"
#include "Queen.h"
#include "Camera.h"
#include "ChessBoard.h"
#include "Level_Battle.h"
#include "Level_ChessToBattle.h"
#include "Level_Chess.h"
#include "Level_MainMenu.h"
#include "Level_GamePlay.h"
#include "Level_Loading.h"
#include "Level_Logo.h"
#include "Level_Chess.h"
#include "Loader.h"
#include "MainApp.h"
#include "Sky.h"
#include "Pawn.h"
#include "Player.h"
#include "Rook.h"
#include "Knight.h"
#include "King.h"
#include "TargetCamera.h"
#include "Terrain.h"
#include "BD_Pawn.h"
#include "BD_Rook.h"
#include "BD_Bishop.h"
#include "BD_Knight.h"
#include "BD_Queen.h"
#include "BD_King.h"


extern HWND g_hWnd;

extern CQueen* g_pClientPlayer;
extern CQueen* g_pServerPlayer;
extern SOCKET g_Socket;
extern sockaddr_in g_ServerAddr;
