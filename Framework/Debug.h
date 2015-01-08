#pragma once

#include "Singleton.h"

class CTerrainMesh;


class CDebug
	: public CSingleton<CDebug>
{
	friend CSingleton;
private:
	LPDIRECT3DVERTEXBUFFER9		m_pGridVB;
	LPDIRECT3DVERTEXBUFFER9		m_pLineVB;
	int							m_iCnt;

private:
	CTerrainMesh*		m_pTerrain;
	LPDIRECT3DDEVICE9	m_pDevice;
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

