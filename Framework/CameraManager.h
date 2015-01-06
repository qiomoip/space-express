#pragma once
#include "Singleton.h"
#include "define.h"

class CCamera;

class CCameraManager : public CSingleton<CCameraManager>
{
private:

	friend CSingleton;
	CCameraManager(void);
	~CCameraManager(void);

	map<string, CCamera*>*		m_mapCamera;

public:

	void						Init();

	CCamera*					GetCamera(string _CameraName);
	void						SetTransform(string _CameraName);

	void						AddCamera(string _CameraName);
};

