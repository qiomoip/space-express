#pragma once
#include "define.h"
#include "Singleton.h"

class CDebug
	: public CSingleton<CDebug>
{
	friend CSingleton;
private:
	LPDIRECT3DVERTEXBUFFER9		m_pGridVB;

public:
	void Initialize();
	void Update();
	void Render();
	void Destroy();

public:
	void CreateVertexBuffer();
	void DrawInfo();
	void DrawGrid();

private:
	CDebug(void);
	~CDebug(void);
};

