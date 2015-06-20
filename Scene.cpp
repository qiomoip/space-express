#include "Scene.h"
#include "Light.h"
#include "Device.h"
#include "Debug.h"
#include "ObjectManager.h"
#include "CameraManager.h"

CScene::CScene(void)
	: m_pDevice(NULL)
	, m_bChangeScene(false)
{
}


CScene::~CScene(void)
{
	Destroy();
}

HRESULT CScene::Init()
{
	m_pDevice = _SINGLE(CDevice)->GetDevice();

	if(!m_pDevice)
		return E_FAIL;

	return S_OK;
}

void CScene::Render()
{
	// Clear the backbuffer to a blue color
	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | 
		D3DCLEAR_STENCIL, D3DCOLOR_XRGB( 200, 200, 200 ), 1.0f, 0 );

	// Begin the scene
	if( SUCCEEDED( m_pDevice->BeginScene() ) )
	{
		// Rendering of scene objects can happen here

		//Camera Transform
		_SINGLE(CCameraManager)->SetTransform(); 

		//Set Light
		_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
		for(unsigned int i = 0; i < m_vecLight.size(); ++i)
		{
			m_pDevice->SetLight(i, m_vecLight[i]->GetLightInfo());
			m_pDevice->LightEnable(i, true);
		}

		//ObjectRender
		_SINGLE(CObjectManager)->Render(); 

#ifdef _DEBUG

		//Debug Render
		_SINGLE(CDebug)->Render();
		_SINGLE(CDebug)->InitFaceCount();
		//_SINGLE(CFrustum)->Render();

#endif

		// End the scene
		m_pDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	m_pDevice->Present( NULL, NULL, NULL, NULL );
}

void CScene::Destroy()
{
	_SINGLE(CObjectManager)->CleanUp();
	_SINGLE(CCameraManager)->Destroy();
		for(unsigned int i = 0; i < m_vecLight.size(); ++i)
		Safe_Delete(m_vecLight[i]);
		m_vecLight.clear();
}
