#include "CameraManager.h"
#include "Device.h"
#include "Camera.h"
#include "ThirdCam.h"
#include "KeyManager.h"

#ifdef _DEBUG
#include "Debug.h"
#endif

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

	
#ifdef _DEBUG
	LPTSTR vPos = new TCHAR[100];
	LPTSTR vLook = new TCHAR[100];
	LPTSTR vUp = new TCHAR[100];
	LPTSTR vRight = new TCHAR[100];
	_SINGLE(CDebug)->VectorToString(vPos,  m_pCurCam->GetCameraInfo().vPos );
	_SINGLE(CDebug)->VectorToString(vLook, m_pCurCam->GetCameraInfo().vLook );
	_SINGLE(CDebug)->VectorToString(vUp, m_pCurCam->GetCameraInfo().vUp );
	_SINGLE(CDebug)->VectorToString(vRight, m_pCurCam->GetCameraInfo().vRight );
	_SINGLE(CDebug)->AddStaticLog(true, _T("%s나는 문자열이다."), _T("string") );
	_SINGLE(CDebug)->AddStaticLog( true, _T("카메라 정보 출력\nvPos : %s\nvLook : %s\nvUp : %s\nvRight : %s\nfAngle : %d, %d, %d"),
		vPos, vLook, vUp, vRight, m_pCurCam->GetCameraInfo().iAngle[0], m_pCurCam->GetCameraInfo().iAngle[1], m_pCurCam->GetCameraInfo().iAngle[2]);

	Safe_Delete_Array(vPos);
	Safe_Delete_Array(vLook);
	Safe_Delete_Array(vUp);
	Safe_Delete_Array(vRight);
#endif
}

void CCameraManager::Input()
{
	CheckKey();
	
	CAMERA pCamera = m_pCurCam->GetCameraInfo();

	memset(pCamera.iDir, 0, sizeof(int) * AT_MAX);
	memset(pCamera.iAngle, 0, sizeof(int) * AT_MAX);
	const KEYINFO* pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_FRONT);

	if(!pInfo)
		return;

	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iDir[AT_Z] = 1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_BACK);
	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iDir[AT_Z] = -1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_RIGHT);
	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iDir[AT_X] = 1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_LEFT);
	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iDir[AT_X] = -1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_UP);
	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iDir[AT_Y] = 1;
	}
	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_DOWN);
	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iDir[AT_Y] = -1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_TURN_RIGHT);
	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iAngle[AT_Y] = 1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_TURN_LEFT);
	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iAngle[AT_Y] = -1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_TURN_UP);
	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iAngle[AT_X] = -1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_TURN_DOWN);
	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iAngle[AT_X] = 1;
	}

	m_pCurCam->SetCamera( pCamera );
	
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
	const KEYINFO* pInfo = _SINGLE(CKeyManager)->GetKey("KEY_SPACE");
	if(!pInfo)
		return;

	if(pInfo->bPush)
	{
		if(!m_bChange)
		{
			SetMainCamera("ThirdTestCam");
			m_bChange = true;
		}
		else
		{
			SetMainCamera("MainCamera");
			m_bChange = false;
		}
	}
}

void CCameraManager::Destroy()
{
	Safe_Delete_Array_Map(m_mapCamera);
}

const CCamera*	CCameraManager::GetCurCam() const
{
	return m_pCurCam;
}