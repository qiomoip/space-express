#pragma once
#include "scene.h"
class CMainGameScene :
	public CScene
{
public:
	HRESULT Init();
	void Update();
	void Destroy();

public:
	HRESULT CreateEntity();
	HRESULT CreateBox(LPCWSTR pFileName);
	HRESULT CreateCamera();
	HRESULT CreateLight();

public:
	CMainGameScene(void);
	~CMainGameScene(void);
};

