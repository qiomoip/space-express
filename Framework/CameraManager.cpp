#include "CameraManager.h"
#include "Device.h"
#include "Camera.h"
#include "ThirdCam.h"
#include "KeyManager.h"
#include "Frustum.h"

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
	TCHAR vPos[100] = _T(""); 
	TCHAR vLook[100] = _T("");
	TCHAR vUp[100] = _T("");
	TCHAR vRight[100] = _T("");
	_SINGLE(CDebug)->VectorToString(vPos,  m_pCurCam->GetCameraInfo().vPos );
	_SINGLE(CDebug)->VectorToString(vLook, m_pCurCam->GetCameraInfo().vLook );
	_SINGLE(CDebug)->VectorToString(vUp, m_pCurCam->GetCameraInfo().vUp );
	_SINGLE(CDebug)->VectorToString(vRight, m_pCurCam->GetCameraInfo().vRight );
	
	_SINGLE(CDebug)->AddStaticLog(LOG_CAMERA_INFO_1, _T("vPos : %s"), vPos );
	_SINGLE(CDebug)->AddStaticLog(LOG_CAMERA_INFO_2, _T("vLook : %s"), vLook);
	_SINGLE(CDebug)->AddStaticLog(LOG_CAMERA_INFO_3, _T("vUp : %s"), vUp );
	_SINGLE(CDebug)->AddStaticLog(LOG_CAMERA_INFO_4, _T("vRight : %s"), vRight );
	_SINGLE(CDebug)->AddStaticLog(LOG_CAMERA_INFO_5, _T("fAngle : %d, %d, %d"),
		m_pCurCam->GetCameraInfo().iAngle[0], 
		m_pCurCam->GetCameraInfo().iAngle[1], 
		m_pCurCam->GetCameraInfo().iAngle[2]);
	
#endif
	//절두체 설정
	_SINGLE(CFrustum)->setFrustum( GetCurCam()->GetMatViewProj() );
}

void CCameraManager::Input()
{
	/*키 설정
	W, S : 상하로 회전
	A, D : 좌우로 회전
	HOME, END : 보는 방향으로 전진, 후진
	INSERT, PAGE_UP : UP벡터 방향으로 상승, 하강
	DEL, PAGE_DOWN : RIGHT벡터 방향으로 좌, 우 이동
	*/
	CheckKey();
	
	CAMERA pCamera = m_pCurCam->GetCameraInfo();

	memset(pCamera.iDir, 0, sizeof(int) * AT_MAX);
	memset(pCamera.iAngle, 0, sizeof(int) * AT_MAX);
	const KEYINFO* pInfo /*= _SINGLE(CKeyManager)->GetKey(KEYNAME_FRONT)*/;

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_HOME);
	if(!pInfo)
		return;
	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iDir[AT_Z] = 1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_END);
	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iDir[AT_Z] = -1;
	}
	
	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_PGDN);
	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iDir[AT_X] = 1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_DEL);
	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iDir[AT_X] = -1;
	}
	
	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_INS);
	if(pInfo->bPush || pInfo->bDown)
	{
		pCamera.iDir[AT_Y] = 1;
	}
	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_PGUP);
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

	
#ifdef _DEBUG
	
	//const char* szName = strName.c_str();
	TCHAR szRet[100];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, strName.c_str(), strlen(strName.c_str()) + 1,
		szRet, _tcslen(szRet) + 1);

	_SINGLE(CDebug)->AddStaticLog(LOG_CAMERA_INFO_0, _T("CameraName: %s"), 
		szRet );
#endif

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
	const KEYINFO* pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_SPACE);
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