#pragma once
#include "Engine_Typedef.h"

namespace Engine
{
	typedef struct tagEngineDesc
	{
		HWND			hWnd, hWnd_2;
		WINMODE			eWinMode;
		unsigned int	iWinSizeX, iWinSizeY;
		unsigned int	iNumLevels;

	}ENGINE_DESC;

	typedef struct tagVertexPosTex
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR2		vTexcoord;

		enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };

	}VTXPOSTEX;

	typedef struct tagVertexPosPawn
	{
		D3DXVECTOR3		vPosition;
		_ulong			dwColor;

	}VTXPOSPAWN;


#pragma region RAY_CASTING

	typedef struct tagBoundingBox
	{

	}BOUNDINGBOX;

	typedef struct tagTriangle
	{

	}TRIANGLE;

#pragma endregion


}
