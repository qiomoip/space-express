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
#endif

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <strsafe.h>

#pragma warning( disable : 4996 ) // disable deprecated warning 

#pragma warning( default : 4996 )

using namespace std;

#include "Struct.h"
#include "Enum.h"

#define _SINGLE(T)	T::GetInstance()

//Enum to string.(열겨형을 문자열로 변환 해준다.)
#define EtoS(t)	_T(#t)


template <typename T>
void SAFE_DELETE(T& p)
{
	if(p)
	{
		delete	p;
		p	= NULL;
	}
}

template <typename T>
void Safe_Delete_Array(T& p)
{
	if(p)
	{
		delete	[]	p;
		p	= NULL;
	}
}