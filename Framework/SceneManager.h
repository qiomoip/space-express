#pragma once
#include "Singleton.h"

class CScene;

class CSceneManager
	: public CSingleton<CSceneManager>
{
	friend CSingleton;
private:
	CScene*	m_pCurScene;	//���� �� 
	CScene*	m_pNextScene;	//���� �� (���࿡ ���� ���� �����ϸ鼭 ���� ���� �ε��ϰ� �ʹٸ� ���??)
	map<string, CScene*>	m_mapScene;		//���� ����
	eSCENE_TYPE		m_eNextScene;

public:
	void Init();
	void Update();
	void Render();
	void Destroy();
	void Input();

public:
	void CreateScene(const eSCENE_TYPE& eScene);	//����� ����

public:
	void PushScene(CScene* pScene);		//���� ���� ���� ���� ����
	void ChangeScene();	//��������� ���� ������ ��ü
	void PushScene(const eSCENE_TYPE& eScene);

public:
	const CScene*	GetCurrentScene() const;

private:
	CSceneManager(void);
	~CSceneManager(void);
};

