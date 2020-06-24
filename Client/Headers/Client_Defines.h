#pragma once

namespace Client
{
	const unsigned int g_iWinSizeX = 1280;
	const unsigned int g_iWinSizeY = 720;
	

	enum SCENEID { SCENE_STATIC, SCENE_LOADING, SCENE_MENU, SCENE_STAGE, SCENE_END };


}	



using namespace Client;
extern HWND g_hWnd;

#include <functional>
#include <time.h>
#include "Client_Struct.h"

extern RECT Make_Rect(D3DXVECTOR4 _vPos, D3DXVECTOR4 _vSize);