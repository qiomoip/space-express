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


/*
define
*/

#define _SINGLE(T)	T::GetInstance()