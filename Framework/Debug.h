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
	//�׸���� ����
	LPDIRECT3DVERTEXBUFFER9		m_pGridVB;
	LPDIRECT3DVERTEXBUFFER9		m_pLineVB;
	D3DMATERIAL9				m_tGridMaterial;
	int							m_iCnt;
	//�ͷ��� ����0
	CEntity*		m_pTerrain;

	//D3D ��Ʈ ����
	LPD3DXFONT		m_pFont;
	D3DXFONT_DESC	m_Desc;
	//RECT			m_FontRect;
	RECT			m_LogRect;
	RECT			m_StaticLogRect;

	//��ø�� �α�
	LPTSTR*			m_Log;
	//���� �α� 
	LPTSTR*			m_StaticLog;
	//�α��� ��
	int				m_LogCount;
	int				m_StaticLogCount;

	//���� �߰� 
	LPD3DXLINE		m_Line;
	//�׸� ���� ���
	D3DXVECTOR3		m_vList[LOG_COUNT][2];
	//���� ����
	D3DXCOLOR		m_ColorList[LOG_COUNT];
	//���� ����
	int				m_LineCount;

	//�׷����� ������ �� 
	UINT			m_FaceCount;

	//FPS
	UINT			m_FPS;
	//FPS������ �ð�
	DWORD			m_StartTime;
	DWORD			m_EndTime;
	DWORD			m_ElapsedTime;

	//���̾������� Ʈ����
	bool			m_bWireFrame;

public:
	void CreateVertexBuffer();
	void DrawInfo();
	//void DrawGrid();

	//�α� �ʱ�ȭ
	VOID			InitLog();
	//��Ʈ ����� ���� D3D��Ʈ ����
	VOID			InitFont();
	//���� �ʱ�ȭ
	void			InitLine();
	
	//�Ｎ���� ��� �޼���
	HRESULT			DrawStaticLog();
	//�׻� ȭ�鿡 ��� �޼���
	HRESULT			DrawLog();
	//���͸� �׸��� �Լ�
	void			DrawLine();
	//�α� �߰�
	//HRESULT		AddLog(LPTSTR _log, ...);
	//Ư�� �ε����� �α� �߰�
	HRESULT			AddLog(int _idx, LPTSTR _log, ...);
	//������ ��ġ(�������)�� �α� ���.enum���� ��ȣ ����
	HRESULT			AddStaticLog(int, LPTSTR , ...);
	//���� ����� ���� ���ڿ� ��ȯ
	HRESULT			VectorToString(LPTSTR dest, D3DXVECTOR3 vec);
	//����� ���� �߰�
	void			AddLine(D3DXVECTOR3, D3DXVECTOR3, D3DCOLOR );
	//������� �ʱ�ȭ(���� �Լ� ���۽� �ʱ�ȭ)
	void			InitFaceCount();
	//������� �߰�(�׸������� ȣ��)
	void			AddFaceCount(UINT);
	//�ʴ� �����Ӽ� üũ
	void			CheckFPS();
	
	DWORD			GetDeltaTime(){return m_ElapsedTime;}

	void			ResetLine();
	
private:
	CDebug(void);
	~CDebug(void);
};

