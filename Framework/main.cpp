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
//#include "Engine.h"

#ifdef _DEBUG
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif
//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc(234);
#endif

	//_wsetlocale(LC_ALL, _T("korean") );

	UNREFERENCED_PARAMETER( hInst );

	CApp* pApp = new CApp();

	if(FAILED(pApp->Initialize(
		hInst, _T("ExpressWork"), _T("qiomoip"), SCREEN_WIDTH, SCREEN_HEIGHT)))
	{
		Safe_Delete(pApp);
		return 0;
	}

	pApp->Run();

	Safe_Delete(pApp);

	#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}



