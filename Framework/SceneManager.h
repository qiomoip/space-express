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
	map<string, CScene*>	m_mapScene;		//씬들 집합
	eSCENE_TYPE		m_eNextScene;

public:
	void Init();
	void Update();
	void Render();
	void Destroy();
	void Input();

public:
	void CreateScene(const eSCENE_TYPE& eScene);	//현재씬 설정

public:
	void PushScene(CScene* pScene);		//현재 씬의 다음 씬을 넣음
	void ChangeScene();	//현재씬에서 다음 씬으로 교체
	void PushScene(const eSCENE_TYPE& eScene);

public:
	const CScene*	GetCurrentScene() const;

private:
	CSceneManager(void);
	~CSceneManager(void);
};

