#pragma once
#include "basebutton.h"
class CScene;

class CSceneButton :
	public CBaseButton
{
private:
	eSCENE_TYPE	m_eScene;
	CScene*		m_pScene;

public:
	void Initialize();
	void Update();

public:
	void Schedule();

public:
	void SetSceneType(const eSCENE_TYPE& eType);
	void SetScene(CScene* pScene);

public:
	CSceneButton(void);
	~CSceneButton(void);
};

