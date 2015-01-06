#include "CameraManager.h"
#include "Device.h"
#include "Camera.h"

CCameraManager::CCameraManager(void)
{
}


CCameraManager::~CCameraManager(void)
{
}

void CCameraManager::Init()
{
	m_mapCamera = new map<string, CCamera*>;
}

CCamera* CCameraManager::GetCamera(string _CameraName)
{
	return m_mapCamera->find(_CameraName)->second;
}

void	CCameraManager::SetTransform(string _CameraName)
{
	_SINGLE(CDevice)->GetDevice()->SetTransform( D3DTS_VIEW, 
		GetCamera( _CameraName )->GetMatView() );
	_SINGLE(CDevice)->GetDevice()->SetTransform( D3DTS_PROJECTION, 
		GetCamera( _CameraName )->GetMatProj() );
}

void CCameraManager::AddCamera(string _CameraName)
{
	m_mapCamera->insert( pair<string, CCamera*>(_CameraName, new CCamera()) );
}