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
	//그리드용 변수
	LPDIRECT3DVERTEXBUFFER9		m_pGridVB;
	LPDIRECT3DVERTEXBUFFER9		m_pLineVB;
	D3DMATERIAL9				m_tGridMaterial;
	int							m_iCnt;
	//터레인 변수
	CEntity*		m_pTerrain;

	//D3D 폰트 변수
	LPD3DXFONT		m_pFont;
	D3DXFONT_DESC	m_Desc;
	//RECT			m_FontRect;
	RECT			m_LogRect;
	RECT			m_StaticLogRect;

	//중첩식 로그
	LPTSTR*			m_Log;
	//고정 로그 
	LPTSTR*			m_StaticLog;
	//로그의 수
	int				m_LogCount;
	int				m_StaticLogCount;

	//그려지는 폴리곤 수 
	UINT			m_FaceCount;

	//FPS
	UINT			m_FPS;
	//FPS측정용 시간
	DWORD			m_StartTime;
	DWORD			m_EndTime;
	DWORD			m_ElapsedTime;

	//와이어프레임 트리거
	bool			m_bWireFrame;

public:
	void CreateVertexBuffer();
	void DrawInfo();
	//void DrawGrid();

	//로그 초기화
	VOID			InitLog();
	//폰트 출력을 위한 D3D폰트 설정
	VOID			InitFont();
	
	//즉석에서 띄울 메세지
	HRESULT			DrawStaticLog();
	//항상 화면에 듸울 메세지
	HRESULT			DrawLog();
	//로그 추가
	//HRESULT			AddLog(LPTSTR _log, ...);
	//특정 인덱스에 로그 추가
	HRESULT			AddLog(int _idx, LPTSTR _log, ...);
	//고정된 위치(우측상단)에 로그 출력.enum으로 번호 배정
	HRESULT			AddStaticLog(int, LPTSTR , ...);
	//벡터 출력을 위한 문자열 변환
	HRESULT			VectorToString(LPTSTR dest, D3DXVECTOR3 vec);
	
	//폴리곤수 초기화(렌더 함수 시작시 초기화)
	void			InitFaceCount();
	//폴리곤수 추가(그릴때마다 호출)
	void			AddFaceCount(UINT);
	//초당 프레임수 체크
	void			CheckFPS();
	
	DWORD			GetDeltaTime(){return m_ElapsedTime;}
	
private:
	CDebug(void);
	~CDebug(void);
};

