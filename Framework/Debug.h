#pragma once

#include "Singleton.h"

class CEntity;


class CDebug
	: public CSingleton<CDebug>
{
	friend CSingleton;
private:
	LPDIRECT3DDEVICE9	m_pDevice;
	
public:
	void Initialize();
	void Update();
	void Render();
	void Destroy();
	void Input();

//Debug & Test
private:
	LPDIRECT3DVERTEXBUFFER9		m_pGridVB;
	LPDIRECT3DVERTEXBUFFER9		m_pLineVB;
	int							m_iCnt;

	CEntity*		m_pTerrain;

	

public:
	void CreateVertexBuffer();
	void DrawInfo();
	void DrawGrid();

private:
	CDebug(void);
	~CDebug(void);
};

