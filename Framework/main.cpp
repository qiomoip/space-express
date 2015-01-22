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
	#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc(385);
#endif

//#ifdef _DEBUG
	//_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif

	UNREFERENCED_PARAMETER( hInst );

	CApp* pApp = new CApp();

	if(FAILED(pApp->Initialize(hInst, L"ExpressWork", L"qiomoip", 800, 600)))
	{
		Safe_Delete(pApp);
		return 0;
	}

	pApp->Run();

	Safe_Delete(pApp);

//	#ifdef _DEBUG
//	_CrtDumpMemoryLeaks();
//#endif
	return 0;
}



