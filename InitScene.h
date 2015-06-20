#pragma once
#include "scene.h"
class CInitScene :
	public CScene
{
public:
	HRESULT Init();
	void Update();
	void Destroy();

public:
	HRESULT CreateEntity();
	HRESULT CreateCamera();
	HRESULT CreateLight();

public:
	CInitScene(void);
	~CInitScene(void);
};

