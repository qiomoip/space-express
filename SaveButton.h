#pragma once
#include "basebutton.h"
class CScene;

class CSaveButton :
	public CBaseButton
{
private:
	CScene*	m_pScene;

public:
	void Initialize();
	void Update();

public:
	void Schedule();

public:
	void SetScene(CScene* pScene);

public:
	CSaveButton(void);
	~CSaveButton(void);
};

