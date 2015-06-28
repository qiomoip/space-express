#pragma once
#include "Singleton.h"

class CScene;

class CSceneManager
	: public CSingleton<CSceneManager>
{
	friend CSingleton;
private:
	CScene*	m_pCurScene;	//현재 씬 
	CScene*	m_pNextScene;	//다음 씬 (만약에 현재 씬을 진행하면서 다음 씬을 로드하고 싶다면 사용??)

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

