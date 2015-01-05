//-----------------------------------------------------------------------------
// File: Framework.cpp
//
// Desc: This is the first tutorial for using Direct3D. In this tutorial, all
//       we are doing is creating a Direct3D device and using it to clear the
//       window.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
//#include <d3d9.h>
//#pragma warning( disable : 4996 ) // disable deprecated warning 
#include "define.h"
#include "App.h"
#include "Engine.h"

//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	UNREFERENCED_PARAMETER( hInst );

	CApp* pApp = new CApp();

	if(FAILED(pApp->Initialize(hInst)))
	{
		SAFE_DELETE(pApp);
		return 0;
	}

	pApp->Run();

	SAFE_DELETE(pApp);
	return 0;
}



