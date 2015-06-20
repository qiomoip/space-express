#pragma once

#include "define.h"
/*
카메라 클래스
여러 카메라를 사용할 수도 있기 때문에 싱글톤 아님.
*/

class CCamera
{
protected:
	//D3DXVECTOR3				m_vEyePt;		//vPos
 //   D3DXVECTOR3				m_vLookatPt;	//vLook
 //   D3DXVECTOR3				m_vUpVec;		//vUp
	//D3DXMATRIX				matView;
	//D3DXMATRIX				matProj;
	CAMERA						m_tCam;

public:
	virtual void Init();
	virtual void Update();
	virtual void Input();

public:
	void SetViewMatrix();
	void SetPos(const D3DXVECTOR3& vPos);
	void SetData(const D3DXVECTOR3& vUp, const D3DXVECTOR3& vLook, const D3DXVECTOR3& vRight);
	void SetCamera(const CAMERA&	_tCamera);

public:
	const D3DXMATRIX*			GetMatView(const eVIEW_TYPE& eView = VIEW_PERSPECTIVE)const;
	const D3DXMATRIX*			GetMatProj(const eVIEW_TYPE& eView = VIEW_PERSPECTIVE)const;
	const D3DXMATRIX			GetMatViewProj(const eVIEW_TYPE& eView = VIEW_PERSPECTIVE)const;
	const CAMERA				GetCameraInfo() const;

public:
	void SetTransform(const eVIEW_TYPE& eView = VIEW_PERSPECTIVE);

public:
	CCamera(void);
	virtual ~CCamera(void);
};

