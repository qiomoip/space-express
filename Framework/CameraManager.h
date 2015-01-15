#pragma once
#include "Singleton.h"

class CCamera;
class CInfo;

class CCameraManager : public CSingleton<CCameraManager>
{
private:

	friend CSingleton;
	CCameraManager(void);
	~CCameraManager(void);

	map<eCAMERA_NUM, CCamera*>*				m_mapCamera;
	map<eCAMERA_NUM, CCamera*>::iterator	m_CurCamera;

	CInfo*									m_Info;

public:
	//초기화
	void							Init();
	void							Clean();
	//특정 카메라 반환(존재하지 않는 카메라면 0반환)
	CCamera*						GetCamera(eCAMERA_NUM _CameraName);
	//현재 카메라 변경
	HRESULT							SetCurrentCamera(eCAMERA_NUM _CameraName);
	//현재 카메라 반환
	CCamera*						GetCurrentCamera();
	//특정 카메라로 전환 및 행렬 적용(VIEW, PROJ)
	HRESULT							SetTransform(eCAMERA_NUM _CameraName);
	//현재 카메라 행렬 적용
	HRESULT							SetTransform();
	//카메라 추가
	HRESULT							AddCamera(eCAMERA_NUM _CameraName, D3DXVECTOR3 _vEye, D3DXVECTOR3 _vLookat, D3DXVECTOR3 _vUpVec, bool _isFixed);
	//카메라 이동(보간X, 해당 위치로 순간이동)
	HRESULT							MoveCamera(/*, D3DXVECTOR3 _vPos*/);
	//카메라 전환(보간X, 다른 카메라로 전환)
	HRESULT							ChangeCamera();

	vector<LPTSTR>*							GetCameraInfo();
};

