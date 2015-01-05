#include "App.h"
#include "Engine.h"


CApp::CApp(void)
	: m_hWnd(NULL)
	, m_hInst(NULL)
{
}


CApp::~CApp(void)
{
}

HRESULT CApp::Initialize(HINSTANCE hInst)
{
	m_hInst = hInst;

	CreateWnd();

	if(!m_hWnd)
		return E_FAIL;
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
				_SINGLE(CEngine)->Render();
		}
	}

	UnregisterClass( L"D3D Tutorial", m_hInst );
}

void CApp::CreateWnd()
{
	RegisterWindow();
	// Create the application's window
    m_hWnd = CreateWindow( L"D3D Tutorial", L"D3D Tutorial 01: Framework",
                              WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
							  NULL, NULL, m_hInst, NULL );
}

LRESULT CApp::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
    {
        case WM_DESTROY:
            _SINGLE(CEngine)->Destroy();
            PostQuitMessage( 0 );
            return 0;
		case WM_KEYDOWN:
			switch(wParam)
			{
			case VK_ESCAPE:
				_SINGLE(CEngine)->Destroy();
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
        L"D3D Tutorial", NULL
    };
    return RegisterClassEx( &wc );
}
