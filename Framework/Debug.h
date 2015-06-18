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
	//터레인 변수0
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

	//라인 추가 
	LPD3DXLINE		m_Line;
	//그릴 라인 목록
	D3DXVECTOR3		m_vList[LOG_COUNT][2];
	//라인 색깔
	D3DXCOLOR		m_ColorList[LOG_COUNT];
	//라인 갯수
	int				m_LineCount;

	//그려지는 폴리곤 수 
	UINT			m_FaceCount;

	

	//와이어프레임 트리거
	bool			m_bWireFrame;

	//좌표 출력용 십자가의 크기
	float			m_PosMarkSize;
	
	//3차원 글씨 출력 관련 변수
	LPD3DXMESH		m_Text3D[LOG_COUNT];
	int				m_Text3dCount;
	D3DXVECTOR3		m_Text3dPos[LOG_COUNT];
	D3DXMATRIXA16	m_TextMat;
	D3DXMATRIXA16	m_TextScale;
	D3DXMATRIXA16	m_TextMove;
	D3DXMATRIXA16	m_TextRot;
	LOGFONT			m_FontDefine;
	HDC				m_hdc;
	HFONT			m_hFont;
	D3DMATERIAL9	m_TextMaterial;
	

public:
	void CreateVertexBuffer();
	void DrawInfo();
	//void DrawGrid();

	//로그 초기화
	VOID			InitLog();
	//폰트 출력을 위한 D3D폰트 설정
	VOID			InitFont();
	//라인 초기화
	void			InitLine();
	
	//즉석에서 띄울 메세지
	HRESULT			DrawStaticLog();
	//항상 화면에 듸울 메세지
	HRESULT			DrawLog();
	//3D텍스트 출력
	HRESULT			DrawText3D();
	//벡터를 그리는 함수
	void			DrawLine();
	//로그 추가
	//HRESULT		AddLog(LPTSTR _log, ...);
	//특정 인덱스에 로그 추가
	HRESULT			AddLog(int _idx, LPTSTR _log, ...);
	//고정된 위치(우측상단)에 로그 출력.enum으로 번호 배정
	HRESULT			AddStaticLog(int, LPTSTR , ...);
	//화면에 3차원 텍스트 출력(_isUpdate : 문자열이 바뀌었으면 true)
	HRESULT			AddText3D(int, D3DXVECTOR3, LPTSTR, bool = false);
	//벡터 출력을 위한 문자열 변환
	HRESULT			VectorToString(LPTSTR dest, D3DXVECTOR3 vec);
	//출력할 벡터 추가
	void			AddLine(D3DXVECTOR3, D3DXVECTOR3, D3DCOLOR );
	//좌표 출력용 십자 추가
	void			AddPosMark(D3DXVECTOR3, D3DCOLOR );
	//폴리곤수 초기화(렌더 함수 시작시 초기화)
	void			InitFaceCount();
	//폴리곤수 추가(그릴때마다 호출)
	void			AddFaceCount(UINT);

	void			ResetLine();

	void			ResetText3D();
	
private:
	CDebug(void);
	~CDebug(void);
};

