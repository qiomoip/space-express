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
	//�ʱ�ȭ
	void							Init();
	//ī�޶� ��ȯ(�������� �ʴ� ī�޶�� 0��ȯ)
	CCamera*						GetCamera(eCAMERA_NUM _CameraName);
	//ī�޶� ���� ��� ����(VIEW, PROJ)
	HRESULT							SetTransform(eCAMERA_NUM _CameraName);
	//ī�޶� �߰�
	HRESULT							AddCamera(eCAMERA_NUM _CameraName);
	//ī�޶� �̵�(����X, �ش� ��ġ�� �����̵�)
	HRESULT							MoveCamera(eCAMERA_NUM _CameraName = CAMERA_MAIN/*, 
												D3DXVECTOR3 _vPos*/);
	//ī�޶� ��ȯ(����X, �ش� ��ġ�� �����̵�)
	//HRESULT							ChangeCamera(eCAMERA_NUM _CameraName);
};

