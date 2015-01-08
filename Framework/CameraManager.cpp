#include "CameraManager.h"
#include "InputManager.h"
#include "Device.h"
#include "Camera.h"

CCameraManager::CCameraManager(void) : m_mapCamera(NULL), m_CurCamera(NULL)
{
	Init();
}


CCameraManager::~CCameraManager(void)
{
}

void CCameraManager::Init()
{
	m_mapCamera = new map<eCAMERA_NUM, CCamera*>;
}

CCamera* CCameraManager::GetCamera(eCAMERA_NUM _CameraName)
{
	map<eCAMERA_NUM, CCamera*>::iterator it_find = m_mapCamera->find(_CameraName) ;
	if( it_find != m_mapCamera->end() )	
		return it_find->second;
	//존재하지 않는 카메라 접근
	return 0;
}

HRESULT	CCameraManager::SetTransform(eCAMERA_NUM _CameraName)
{
	if( GetCamera(_CameraName) )
	{
		_SINGLE(CDevice)->GetDevice()->SetTransform( D3DTS_VIEW, 
			GetCamera( _CameraName )->GetMatView() );
		_SINGLE(CDevice)->GetDevice()->SetTransform( D3DTS_PROJECTION, 
			GetCamera( _CameraName )->GetMatProj() );
		return S_OK;
	}
	return S_FALSE;
}

HRESULT CCameraManager::AddCamera(eCAMERA_NUM _CameraName)
{
	bool result =  m_mapCamera->insert ( 
		map<eCAMERA_NUM, CCamera*>::value_type (
		_CameraName, new CCamera() )
		).second;
	
	if( result )
	{
		SetTransform(_CameraName);
		return S_OK;
	}
	//키값이 있으면 FALSE;
	return S_FALSE;
}

HRESULT CCameraManager::MoveCamera(eCAMERA_NUM _CameraName/*, D3DXVECTOR3 _vPos*/)
{
	CCamera* curCamera = GetCamera(_CameraName) ;
	if(curCamera )
	{	
		if(_SINGLE(CInputManager)->GetKeyInput(KEY_LEFT) )
			curCamera->MoveCamera(D3DXVECTOR3(-0.1f, 0.0f, 0.0f));
		if(_SINGLE(CInputManager)->GetKeyInput(KEY_RIGHT) )
			curCamera->MoveCamera(D3DXVECTOR3(0.1f, 0.0f, 0.0f));
		return S_OK;
	}
	return S_FALSE;
}

//HRESULT CCameraManager::ChangeCamera(eCAMERA_NUM _CameraName)
//{
//
//	return S_OK;
//}