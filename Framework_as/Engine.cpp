#include "Engine.h"
#include "Device.h"

CEngine::CEngine(void)
	: m_pDevice(NULL)
	, m_Name(NULL)
{
}

CEngine::~CEngine(void)
{
}

VOID CEngine::SetProjectName(LPCWSTR _name)
{
	const LPCWSTR name = _name;
	m_Name = name;
}

VOID CEngine::Render()
{
	if( NULL == m_pDevice->GetDevice() )
        return;

    // Clear the backbuffer to a blue color
    m_pDevice->GetDevice()->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( m_pDevice->GetDevice()->BeginScene() ) )
    {
        // Rendering of scene objects can happen here

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

	return S_OK;
}

VOID CEngine::Destroy()
{
	if(m_pDevice)
		m_pDevice->Cleanup();
}