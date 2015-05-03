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
	//�ͷ��� ����
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

	//�׷����� ������ �� 
	UINT			m_FaceCount;

	//FPS
	UINT			m_FPS;
	//FPS������ �ð�
	DWORD			m_StartTime;
	DWORD			m_EndTime;
	DWORD			m_ElapsedTime;

public:
	void CreateVertexBuffer();
	void DrawInfo();
	void DrawGrid();

	VOID			InitLog();
	VOID			InitFont();
	//�����α� ���
	HRESULT			DrawStaticLog();
	//�α� ���
	HRESULT			DrawLog();
	//Ư�� �ε����� �α� �߰�
	HRESULT			AddLog(int _idx, LPTSTR _log, ...);
	//������ ��ġ(�������)�� �α� ���.enum���� ��ȣ ����
	HRESULT			AddStaticLog(int, LPTSTR , ...);
	//���� ����� ���� ���ڿ� ��ȯ
	HRESULT			VectorToString(LPTSTR dest, D3DXVECTOR3 vec);
	
	//������� �ʱ�ȭ(���� �Լ� ���۽� �ʱ�ȭ)
	void			InitFaceCount();
	//������� �߰�(�׸������� ȣ��)
	void			AddFaceCount(UINT);

	void			CheckFPS();
	
private:
	CDebug(void);
	~CDebug(void);
};

