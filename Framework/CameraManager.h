#pragma once

#include "Singleton.h"

class CCamera;

class CCameraManager : public CSingleton<CCameraManager>
{
private:

	friend CSingleton;
	CCameraManager(void);
	~CCameraManager(void);

	map<string, CCamera*>		m_mapCamera;
	CCamera*					m_pCurCam;

	bool						m_bChange;

public:

	void						Init();
	void						Update();
	void						Input();
	void						Destroy();

	void						CheckKey();

	bool						SetMainCamera(const string& strName);

	CCamera*					GetCamera(const string& _CameraName);
	const CCamera*				GetCurCam() const;
	void						SetTransform(const string& _CameraName, const eVIEW_TYPE& eView = VIEW_PERSPECTIVE);
	void						SetTransform(const eVIEW_TYPE& eView = VIEW_PERSPECTIVE);


	CCamera* 					CreateCamera(const eCAMERA_NUM& eCam);

	void						AddCamera(const string& _CameraName, CCamera* pCam);

	void						MoveCamera(const string& _CameraName, 
		D3DXVECTOR3 _vPos);
};

