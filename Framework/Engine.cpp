#include "Engine.h"
#include "Device.h"
#include "Debug.h"
#include "Camera.h"
#include "CameraManager.h"
#include "KeyManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "TString.h"

CEngine::CEngine(void)
	: m_pDevice(NULL)
	, m_Name(NULL)
{
}

CEngine::~CEngine(void)
{
	Destroy();
}



HRESULT CEngine::Initialize(HWND hWnd)
{
	m_pDevice = _SINGLE(CDevice);

	if(FAILED(m_pDevice->Initialize(hWnd)))
	{
		return E_FAIL;
	}

	//Camera
	CCamera* pCam = _SINGLE(CCameraManager)->CreateCamera(CN_THIRD);
	_SINGLE(CCameraManager)->AddCamera("MainCamera", pCam);
	_SINGLE(CCameraManager)->SetMainCamera("MainCamera");

	//Camera
	CCamera* pCam1 = _SINGLE(CCameraManager)->CreateCamera(CN_THIRD);
	pCam1->SetPos(D3DXVECTOR3(10.f, 0.f, -10.f));
	_SINGLE(CCameraManager)->AddCamera("ThirdTestCam", pCam1);

	//Key
	_SINGLE(CKeyManager)->Initialize();

#ifdef _DEBUG
	_SINGLE(CDebug)->Initialize();
#endif

	_SINGLE(CResourceManager)->Load();

	return S_OK;
}

void CEngine::Update()
{
	_SINGLE(CCameraManager)->Update();
	_SINGLE(CDebug)->Update();
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

		//Camera Transform
		_SINGLE(CCameraManager)->SetTransform();

		//Debug Render
		
		_SINGLE(CDebug)->Render();

        // End the scene
        m_pDevice->GetDevice()->EndScene();
    }

    // Present the backbuffer contents to the display
    m_pDevice->GetDevice()->Present( NULL, NULL, NULL, NULL );
}

VOID CEngine::Destroy()
{
	_SINGLE(CTString)->KillInstance();
	_SINGLE(CObjectManager)->KillInstance();
	_SINGLE(CResourceManager)->KillInstance();
	_SINGLE(CCameraManager)->KillInstance();
	_SINGLE(CKeyManager)->KillInstance();
	

#ifdef _DEBUG
	_SINGLE(CDebug)->KillInstance();
#endif

	if(m_pDevice)
		m_pDevice->KillInstance();
}

void CEngine::Input()
{
	_SINGLE(CKeyManager)->SetKeyState();
	_SINGLE(CCameraManager)->Input();

#ifdef _DEBUG
	_SINGLE(CDebug)->Input();
#endif
}