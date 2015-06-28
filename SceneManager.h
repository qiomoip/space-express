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

public:
	void Update();
	void Render();
	void Destroy();

public:
	void CreateScene(eSCENE_TYPE& eScene);

public:
	const CScene*	GetCurrentScene() const;

private:
	CSceneManager(void);
	~CSceneManager(void);
};

