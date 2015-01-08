#include "Engine.h"
#include "Device.h"
#include "Debug.h"
#include "Camera.h"
#include "CameraManager.h"
#include "KeyManager.h"

CEngine::CEngine(void)
	: m_pDevice(NULL)
	, m_Name(NULL)
{
}

CEngine::~CEngine(void)
{
}

VOID CEngine::Render()
{
	if( NULL == m_pDevice->GetDevice() )
        return;

    // Clear the backbuffer to a blue color
    m_pDevice->GetDevice()->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 200, 200, 200 ), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( m_pDevice->GetDevice()->BeginScene() ) )
    {
        // Rendering of scene objects can happen here

		//Debug Render
		_SINGLE(CDebug)->Render();

        // End the scene
        m_pDevice->GetDevice()->EndScene();
    }

    // Present the backbuffer contents to the display
    m_pDevice->GetDevice()->Present( NULL, NULL, NULL, NULL );
}

HRESULT CEngine::Initialize(HWND hWnd)
{
	m_pDevice = _SINGLE(CDevice);

	if(FAILED(m_pDevice->Initialize(hWnd)))
	{
		return E_FAIL;
	}

	//Camera
	_SINGLE(CCameraManager)->AddCamera(CN_MAIN);
	_SINGLE(CCameraManager)->SetTransform(CN_MAIN);

#ifdef _DEBUG
	_SINGLE(CDebug)->Initialize();
#endif

	return S_OK;
}

void CEngine::Update()
{
	_SINGLE(CKeyManager)->SetKeyState();
	_SINGLE(CCameraManager)->Update();
	_SINGLE(CDebug)->Update();
}

VOID CEngine::Destroy()
{
	if(m_pDevice)
		m_pDevice->Cleanup();

#ifdef _DEBUG
	_SINGLE(CDebug)->KillInstance();
#endif
}