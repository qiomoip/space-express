#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <map>
#include <d3dx9.h>
#include <d3d9.h>
#include <algorithm>
#include <process.h>
#include <conio.h>
#include <assert.h>
#include <string>
#include <sstream>

#ifdef	_DEBUG
#include <crtdbg.h>
#define new new(_CLIENT_BLOCK, __FILE__,  __LINE__)
#endif

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <strsafe.h>
#include <string.h>
#include <locale.h>
#include <memory>

#pragma warning( disable : 4996 ) // disable deprecated warning 
//#pragma warning( disable : 4244 )

using namespace std;

#include "Enum.h"
#include "struct.h"
#include "function.h"


/*
enum
*/
enum MESH_TYPE
{
	ET_ANI,
	ET_STATIC,
	ET_TERRAIN,
	ET_END,
};



enum KEY
{
	KEYNAME_START,
	KEYNAME_SPACE,
	KEYNAME_FRONT,
	KEYNAME_BACK,
	KEYNAME_RIGHT,
	KEYNAME_LEFT,
	KEYNAME_HOME,
	KEYNAME_END,
	KEYNAME_INS,
	KEYNAME_DEL,
	KEYNAME_PGUP,
	KEYNAME_PGDN,
	KEYNAME_TURN_UP,
	KEYNAME_TURN_DOWN,
	KEYNAME_TURN_RIGHT,
	KEYNAME_TURN_LEFT,
	KEYNAME_TURN_CLOCKWISE,
	KEYNAME_TURN_NCLOCKWISE,
	KEYNAME_WIREFRAME_TRIGGER,
};

/*
define
*/

#define _SINGLE(T)	T::GetInstance()

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768



#define COLOR_RED      D3DCOLOR_ARGB(255, 255, 000, 000)
#define COLOR_GREEN    D3DCOLOR_ARGB(255, 127, 255, 000)
#define COLOR_ORANGE   D3DCOLOR_ARGB(255, 255, 140, 000)
#define COLOR_BLUE     D3DCOLOR_ARGB(255, 000, 000, 255)
#define COLOR_YELLOW   D3DCOLOR_ARGB(255, 255, 255,  51)
#define COLOR_BLACK    D3DCOLOR_ARGB(255, 000, 000, 000)
#define COLOR_GREY     D3DCOLOR_ARGB(255, 112, 112, 112)
#define COLOR_GOLD     D3DCOLOR_ARGB(255, 255, 215, 000)
#define COLOR_PINK     D3DCOLOR_ARGB(255, 255, 192, 203)
#define COLOR_PURPLE   D3DCOLOR_ARGB(255, 128, 000, 128)
#define COLOR_WHITE	   D3DCOLOR_ARGB(255, 255, 255, 249)
#define COLOR_CYAN     D3DCOLOR_ARGB(255, 000, 255, 255)
#define COLOR_MAGENTA  D3DCOLOR_ARGB(255, 255, 000, 255)

#define LOG_COUNT		30