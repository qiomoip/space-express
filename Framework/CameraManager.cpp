#include "CameraManager.h"
#include "Device.h"
#include "Camera.h"
#include "ThirdCam.h"
#include "KeyManager.h"

CCameraManager::CCameraManager(void)
	: m_bChange(false)
	, m_pCurCam(NULL)
{
}


CCameraManager::~CCameraManager(void)
{
	Destroy();
}

void CCameraManager::Init()
{
}

CCamera* CCameraManager::GetCamera(const string& _CameraName)
{
	if( m_mapCamera.find(_CameraName) != m_mapCamera.end() )	
		return m_mapCamera.find(_CameraName)->second;
	else 
		return 0;
}

void	CCameraManager::SetTransform(const string& _CameraName)
{
	CCamera* pCam = GetCamera(_CameraName);
	if(pCam)
	{
		pCam->SetTransform();
	}
	else //존재하지 않는 카메라 접근
		assert(false);
}

void	CCameraManager::SetTransform()
{
	if(m_pCurCam)
		m_pCurCam->SetTransform();
}

void CCameraManager::Update()
{
	map<string, CCamera*>::iterator iter = m_mapCamera.begin();

	for(; iter != m_mapCamera.end(); ++iter)
	{
		iter->second->Update();
	}
}

void CCameraManager::Input()
{
	CheckKey();
	
	m_pCurCam->Input();
}

void CCameraManager::AddCamera(const string& _CameraName, CCamera* pCam)
{
	m_mapCamera.insert( pair<string, CCamera*>(_CameraName, pCam) );
}

bool CCameraManager::SetMainCamera(const string& strName)
{
	map<string, CCamera*>::iterator iter = m_mapCamera.find(strName);

	if(iter == m_mapCamera.end())
	{
		return false;
	}
	m_pCurCam = iter->second;
	return true;
}

CCamera* CCameraManager::CreateCamera(const eCAMERA_NUM& eCam)
{
	CCamera* pCam = NULL;
	switch(eCam)
	{
	case CN_THIRD:
		pCam = new CThirdCam;
		break;
	case CN_DEFAULT:
		pCam = new CCamera;
		break;
	default:
		pCam = NULL;
		break;
	}
	if(!pCam)
		return NULL;

	pCam->Init();

	return pCam;
}

void CCameraManager::CheckKey()
{
	//const KEYINFO* pInfo = _SINGLE(CKeyManager)->GetKey("KEY_SPACE");
	//if(!pInfo)
	//	return;

	//if(pInfo->bPush)
	//{
	//	if(!m_bChange)
	//	{
	//		SetMainCamera("ThirdTestCam");
	//		m_bChange = true;
	//	}
	//	else
	//	{
	//		SetMainCamera("MainCamera");
	//		m_bChange = false;
	//	}
	//}
}

void CCameraManager::Destroy()
{
	Safe_Delete_Array_Map(m_mapCamera);
}

const CCamera*	CCameraManager::GetCurCam() const
{
	return m_pCurCam;
}