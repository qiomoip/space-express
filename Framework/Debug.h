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

	//D3D 폰트 변수
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
	//즉석에서 띄울 메세지
	HRESULT			DrawFont();
	//항상 화면에 듸울 메세지
	HRESULT			DrawLog();
	//로그 추가
	HRESULT			AddLog(LPTSTR _log, ...);
	//특정 인덱스에 로그 추가
	HRESULT			AddLog(int _idx, LPTSTR _log, ...);
	//고정된 위치(우측상단)에 로그 출력
	HRESULT			AddStaticLog(LPTSTR _log, bool isOverwrite, ...);
	

private:
	CDebug(void);
	~CDebug(void);
};

