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

	typedef struct tagVertexCubeTex
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vTexcoord;

	}VTXCUBETEX;

	typedef struct tagVertexPosPawn
	{
		D3DXVECTOR3		vPosition;
		_ulong			dwColor;

	}VTXPOSPAWN;


#pragma region RAY_CASTING

	// 예시용 AABB 구조체
	typedef struct tagBoundingBox {
		D3DXVECTOR3 vMin;
		D3DXVECTOR3 vMax;

	}BOUNDINGBOX;

	// 예시용 Triangle 구조체
	typedef struct tagTriangle {
		D3DXVECTOR3 vP0, vP1, vP2;

	}TRIANGLE;

#pragma endregion


}
