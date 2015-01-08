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
	else 
		return 0;
}

void	CCameraManager::SetTransform(eCAMERA_NUM _CameraName)
{
	if( GetCamera(_CameraName) )
	{
		_SINGLE(CDevice)->GetDevice()->SetTransform( D3DTS_VIEW, 
			GetCamera( _CameraName )->GetMatView() );
		_SINGLE(CDevice)->GetDevice()->SetTransform( D3DTS_PROJECTION, 
			GetCamera( _CameraName )->GetMatProj() );
	}
	else //존재하지 않는 카메라 접근
		assert(false);
}

void CCameraManager::AddCamera(eCAMERA_NUM _CameraName)
{
	m_mapCamera->insert( pair<eCAMERA_NUM, CCamera*>(_CameraName, new CCamera()) );
}