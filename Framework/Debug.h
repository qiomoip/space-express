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

	//D3D ��Ʈ ����
	LPD3DXFONT		m_pFont;
	D3DXFONT_DESC	m_Desc;
	RECT			m_FontRect;
	RECT			m_LogRect;

	LPTSTR*			m_Log;
	LPTSTR			m_StaticLog;
	int				m_LogCount;


public:
	void CreateVertexBuffer();
	void DrawInfo();
	void DrawGrid();

	VOID			InitLog();
	VOID			InitFont();
	//�Ｎ���� ��� �޼���
	HRESULT			DrawFont();
	//�׻� ȭ�鿡 ��� �޼���
	HRESULT			DrawLog();
	//�α� �߰�
	HRESULT			AddLog(LPTSTR _log, ...);
	//Ư�� �ε����� �α� �߰�
	HRESULT			AddLog(int _idx, LPTSTR _log, ...);
	//������ ��ġ(�������)�� �α� ���
	HRESULT			AddStaticLog(LPTSTR _log, bool isOverwrite, ...);
	

private:
	CDebug(void);
	~CDebug(void);
};

