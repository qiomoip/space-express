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
	//�ʱ�ȭ
	void							Init();
	void							Clean();
	//Ư�� ī�޶� ��ȯ(�������� �ʴ� ī�޶�� 0��ȯ)
	CCamera*						GetCamera(eCAMERA_NUM _CameraName);
	//���� ī�޶� ����
	HRESULT							SetCurrentCamera(eCAMERA_NUM _CameraName);
	//���� ī�޶� ��ȯ
	CCamera*						GetCurrentCamera();
	//Ư�� ī�޶�� ��ȯ �� ��� ����(VIEW, PROJ)
	HRESULT							SetTransform(eCAMERA_NUM _CameraName);
	//���� ī�޶� ��� ����
	HRESULT							SetTransform();
	//ī�޶� �߰�
	HRESULT							AddCamera(eCAMERA_NUM _CameraName, D3DXVECTOR3 _vEye, D3DXVECTOR3 _vLookat, D3DXVECTOR3 _vUpVec, bool _isFixed);
	//ī�޶� �̵�(����X, �ش� ��ġ�� �����̵�)
	HRESULT							MoveCamera(/*, D3DXVECTOR3 _vPos*/);
	//ī�޶� ��ȯ(����X, �ٸ� ī�޶�� ��ȯ)
	HRESULT							ChangeCamera();

	vector<LPTSTR>*							GetCameraInfo();
};

