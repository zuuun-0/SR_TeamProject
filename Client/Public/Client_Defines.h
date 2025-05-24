#pragma once

/* 클라이언트에서 사용할 수 있는 공통적인 정의를 모아놓은 파일 */
namespace Client
{
const unsigned int			g_iWinSizeX = { 1280 };
const unsigned int			g_iWinSizeY = { 720 };

enum class LEVEL {
	LEVEL_STATIC,
	LEVEL_LOADING,
	LEVEL_LOGO,
	LEVEL_MAINMENU,
	LEVEL_CHESS,
	LEVEL_CHESSTOBATTLE,
	LEVEL_BATTLE,
	LEVEL_GAMEPLAY,
	LEVEL_END };
}

using namespace Client;

