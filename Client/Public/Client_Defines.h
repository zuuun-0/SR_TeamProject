#pragma once

/* Ŭ���̾�Ʈ���� ����� �� �ִ� �������� ���Ǹ� ��Ƴ��� ���� */
namespace Client
{
const unsigned int			g_iWinSizeX = { 1280 };
const unsigned int			g_iWinSizeY = { 720 };

enum class LEVEL
{
	LEVEL_STATIC,
	LEVEL_LOADING,
	LEVEL_LOGO,
	LEVEL_MAINMENU,
	LEVEL_CHESS,
	LEVEL_CHESSTOBATTLE,
	LEVEL_BATTLE,
	LEVEL_GAMEPLAY,
	LEVEL_END
};
}

enum class WEAPON_TYPE { WEAPON_DMR, WEAPON_SNIPER, WEAPON_BOW, WEAPON_SHOTGUN, WEAPON_GATLING, WEAPON_KNIFE, };

using namespace Client;

