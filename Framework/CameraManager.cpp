#include "CameraManager.h"
#include "Device.h"
#include "Camera.h"

CCameraManager::CCameraManager(void)
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
	if( m_mapCamera->find(_CameraName) != m_mapCamera->end() )	
		return m_mapCamera->find(_CameraName)->second;
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
	if(! (m_mapCamera->insert ( 
		map<eCAMERA_NUM, CCamera*>::value_type (_CameraName, 
												new CCamera() 
												) ).second) )
		return S_OK;
	//키값이 있으면 FALSE;
	return S_FALSE;
}

HRESULT CCameraManager::MoveCamera(eCAMERA_NUM _CameraName, D3DXVECTOR3 _vPos)
{
	CCamera* camera = GetCamera(_CameraName) ;

	if(camera)
	{	
		camera->MoveCamera(_vPos);
	}
	return S_FALSE;
}

HRESULT CCameraManager::ChangeCamera(eCAMERA_NUM _CameraName)
{

	return S_OK;
}