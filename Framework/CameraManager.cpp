#include "CameraManager.h"
#include "InputManager.h"
#include "Device.h"
#include "Camera.h"
#include "Info.h"

CCameraManager::CCameraManager(void) : m_mapCamera(NULL)//, m_CurCamera(NULL)
{
	Init();
}


CCameraManager::~CCameraManager(void)
{
	CleanUp();
}

void CCameraManager::Init()
{
	m_mapCamera = new map<eCAMERA_NUM, CCamera*>;
	m_CurCamera = m_mapCamera->begin();
	
#ifdef _DEBUG
	m_Info = new CInfo();
#endif
}

void CCameraManager::CleanUp()
{
	m_CurCamera = m_mapCamera->begin();
	for(; m_CurCamera != m_mapCamera->end(); ++m_CurCamera)
		SAFE_DELETE(m_CurCamera->second );
	m_mapCamera->clear();
	SAFE_DELETE(m_mapCamera);

#ifdef _DEBUG
	SAFE_DELETE(m_Info );
#endif
}


CCamera* CCameraManager::GetCamera(eCAMERA_NUM _CameraName)
{
	map<eCAMERA_NUM, CCamera*>::iterator it_find = m_mapCamera->find(_CameraName) ;
	if( it_find != m_mapCamera->end() )	
		return  it_find->second;
	//존재하지 않는 카메라 접근
	return 0;
}

HRESULT	CCameraManager::SetCurrentCamera(eCAMERA_NUM _CameraName)
{
	map<eCAMERA_NUM, CCamera*>::iterator it_find = m_mapCamera->find(_CameraName) ;
	if( it_find != m_mapCamera->end() )	
	{
		m_CurCamera = it_find;
		return S_OK;
	}
	return S_FALSE;
}

CCamera* CCameraManager::GetCurrentCamera()
{
	return m_CurCamera->second;
}


HRESULT	CCameraManager::SetTransform(eCAMERA_NUM _CameraName)
{
	CCamera* curCamera = GetCamera(_CameraName);
	if( curCamera )
	{
		SetCurrentCamera(_CameraName);
		_SINGLE(CDevice)->GetDevice()->SetTransform( D3DTS_VIEW, 
			curCamera->GetMatView() );
		_SINGLE(CDevice)->GetDevice()->SetTransform( D3DTS_PROJECTION, 
			curCamera->GetMatProj() );
		return S_OK;
	}
	return S_FALSE;
}

HRESULT	CCameraManager::SetTransform()
{
	_SINGLE(CDevice)->GetDevice()->SetTransform( D3DTS_VIEW, 
		m_CurCamera->second->GetMatView() );
	_SINGLE(CDevice)->GetDevice()->SetTransform( D3DTS_PROJECTION, 
		m_CurCamera->second->GetMatProj() );
	return S_OK;

}

HRESULT CCameraManager::AddCamera(eCAMERA_NUM _CameraName, D3DXVECTOR3 _vEye, D3DXVECTOR3 _vLookat, D3DXVECTOR3 _vUpVec, bool _isFixed)
{
	bool result =  m_mapCamera->insert ( 
		map<eCAMERA_NUM, CCamera*>::value_type (
		_CameraName, new CCamera() )
		).second;
	
#ifdef _DEBUG
	
	//TCHAR info [100];
	//
	//TCHAR num [10];
	//_tcscpy_s(info, _tcslen(info), _T("Camera-") );
	//_itot_s(_CameraName, num, 10);
	//_tcscat_s(info, _tcslen(info) + _tcslen(num)+2 , num);
	//m_Info->m_AddInfo( info );

#endif

	if( result )
	{
		GetCamera(_CameraName)->SetCamera( _vEye, _vLookat, _vUpVec, _isFixed );
		SetTransform(_CameraName);
		return S_OK;
	}
	//키값이 있으면 FALSE;
	return S_FALSE;
}

HRESULT CCameraManager::MoveCamera(/*, D3DXVECTOR3 _vPos*/)
{
	CCamera* curCamera = m_CurCamera->second;
	if( curCamera )
	{	
		if(_SINGLE(CInputManager)->GetKeyInput(KEY_LEFT ) )
			curCamera ->MoveCamera(D3DXVECTOR3(-0.1f, 0.0f, 0.0f));
		if(_SINGLE(CInputManager)->GetKeyInput(KEY_RIGHT) )
			curCamera ->MoveCamera(D3DXVECTOR3(0.1f, 0.0f, 0.0f));

		if(_SINGLE(CInputManager)->GetKeyInput(KEY_UP) )
			curCamera ->MoveCamera(D3DXVECTOR3(0.0f, 0.0f, 0.1f));
		if(_SINGLE(CInputManager)->GetKeyInput(KEY_DOWN) )
			curCamera ->MoveCamera(D3DXVECTOR3(0.0f, 0.0f, -0.1f));

		if(_SINGLE(CInputManager)->GetKeyInput(KEY_ACTION) )
			ChangeCamera();

		if(_SINGLE(CInputManager)->GetKeyInput(KEY_TURN_L) )
			curCamera ->RotateCamera(0.01f );
		else if(_SINGLE(CInputManager)->GetKeyInput(KEY_TURN_R) )
			curCamera ->RotateCamera(-0.01f);
		return S_OK;
	}
	return S_FALSE;
}


HRESULT	CCameraManager::ChangeCamera()
{
	if(++m_CurCamera != m_mapCamera->end() )
	{
		SetTransform();
		return S_OK;
	}
	
	m_CurCamera = m_mapCamera->begin();
	SetTransform();
	return S_FALSE;
}

vector<LPTSTR>*	CCameraManager::GetCameraInfo()
{
	return m_Info->m_GetInfo();
}