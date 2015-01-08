#pragma once
#include "Singleton.h"

class CCamera;

class CCameraManager : public CSingleton<CCameraManager>
{
private:

	friend CSingleton;
	CCameraManager(void);
	~CCameraManager(void);

	map<eCAMERA_NUM, CCamera*>*		m_mapCamera;
	CCamera*						m_CurCamera;

public:
	//초기화
	void							Init();
	//카메라 반환(존재하지 않는 카메라면 0반환)
	CCamera*						GetCamera(eCAMERA_NUM _CameraName);
	//카메라 관련 행렬 적용(VIEW, PROJ)
	HRESULT							SetTransform(eCAMERA_NUM _CameraName);
	//카메라 추가
	HRESULT							AddCamera(eCAMERA_NUM _CameraName);
	//카메라 이동(보간X, 해당 위치로 순간이동)
	HRESULT							MoveCamera(eCAMERA_NUM _CameraName = CAMERA_MAIN/*, 
												D3DXVECTOR3 _vPos*/);
	//카메라 전환(보간X, 해당 위치로 순간이동)
	//HRESULT							ChangeCamera(eCAMERA_NUM _CameraName);
};

