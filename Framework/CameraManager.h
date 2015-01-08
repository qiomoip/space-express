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

public:

	void						Init();
	void						Update();

	CCamera*					GetCamera(eCAMERA_NUM _CameraName);
	void						SetTransform(eCAMERA_NUM _CameraName);

	void						AddCamera(eCAMERA_NUM _CameraName);

	void						MoveCamera(eCAMERA_NUM _CameraName, 
		D3DXVECTOR3 _vPos);
};

