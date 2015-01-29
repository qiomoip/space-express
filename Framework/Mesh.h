#pragma once
#include "define.h"

class CMesh
{
protected:
	
public:
	virtual void Render()PURE;
	virtual void Destroy();

	virtual HRESULT LoadResource(const LPTSTR szMeshName)PURE;

public:
	CMesh(void);
	virtual ~CMesh(void);
};

