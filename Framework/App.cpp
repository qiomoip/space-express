#include "App.h"
#include "Engine.h"
#include "Mouse.h"


CApp::CApp(void)
	: m_hWnd(NULL)
	, m_hInst(NULL)
	, m_lpClassName(NULL)
{
}


CApp::~CApp(void)
{
	Destroy();
}

HRESULT CApp::Initialize(HINSTANCE hInst, LPCWSTR lpClassName, LPCWSTR lpCWindowName, int iWidth, int iHeight)
{
	m_hInst = hInst;
	m_lpClassName = lpClassName;

	CreateWnd(lpCWindowName, iWidth, iHeight);

	if(!m_hWnd)
		return E_FAIL;
	_SINGLE(CMouse)->SetHwnd(m_hWnd);
	return S_OK;
}

VOID CApp::Run()
{
	// Initialize Direct3D
	if( SUCCEEDED( _SINGLE(CEngine)->Initialize( m_hWnd ) ) )
	{
		// Show the window
		ShowWindow( m_hWnd, SW_SHOWDEFAULT );
		UpdateWindow( m_hWnd );

		// Enter the message loop
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));

		while( msg.message != WM_QUIT  )
		{
			if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );

			}
			else
			{
				_SINGLE(CEngine)->Input();
				_SINGLE(CEngine)->Update();
				_SINGLE(CEngine)->Render();
			}
		}
	}

	UnregisterClass( m_lpClassName, m_hInst );
}

void CApp::CreateWnd(LPCWSTR lpCWindowName, int iWidth, int iHeight)
{
	RegisterWindow();

	// Create the application's window
    m_hWnd = CreateWindow( m_lpClassName, lpCWindowName,
                              WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, iWidth, iHeight,
							  NULL, NULL, m_hInst, NULL );
}

LRESULT CApp::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
		case WM_KEYDOWN:
			switch(wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage( 0 );
				break;
			}
			break;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

ATOM CApp::RegisterWindow()
{
	WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, CApp::MsgProc, 0L, 0L,
        m_hInst, NULL, NULL, NULL, NULL,
        m_lpClassName, NULL
    };
    return RegisterClassEx( &wc );
}

void CApp::Destroy()
{
	_SINGLE(CMouse)->KillInstance();
	_SINGLE(CEngine)->KillInstance();
}