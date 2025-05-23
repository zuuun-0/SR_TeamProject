#pragma once
#pragma warning(disable : 4251)

#include <Windows.h>
#include <algorithm>
#include <cassert>
#include <ctime>
#include <d3d9.h>
#include <d3dx9.h>
#include <functional>
#include <list>
#include <map>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;

#include "Engine_Enum.h"
#include "Engine_Function.h"
#include "Engine_Macro.h"
#include "Engine_Struct.h"
#include "Engine_Typedef.h"

#include "Base.h"
#include "Component.h"
#include "GameInstance.h"
#include "Input_Manager.h"
#include "Graphic_Device.h"
#include "Layer.h"
#include "Level.h"
#include "Level_Manager.h"
#include "Object_Manager.h"
#include "Prototype_Manager.h"
#include "Renderer.h"
#include "Timer.h"
#include "Timer_Manager.h"
#include "Transform.h"
#include "UIObject.h"
#include "VIBuffer.h"
#include "VIBuffer_Rect.h"
#include "VIBuffer_Cube.h"
#include "VIBuffer_Terrain.h"
#include "VIBuffer_Board.h"

#pragma region CHESS_PIECES

#include "VIBuffer_Pawn.h"
#include "VIBuffer_Rook.h"
#include "VIBuffer_Bishop.h"
#include "VIBuffer_Knight.h"
#include "VIBuffer_Queen.h"
#include "VIBuffer_King.h"

#pragma endregion


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 

#endif

using namespace Engine;
