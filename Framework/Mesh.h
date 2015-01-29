#pragma once
#include "define.h"

class CMesh
{
public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	CMesh(void);
	virtual ~CMesh(void);
};

