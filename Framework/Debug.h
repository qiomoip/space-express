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

	

	//���̾������� Ʈ����
	bool			m_bWireFrame;

	//��ǥ ��¿� ���ڰ��� ũ��
	float			m_PosMarkSize;
	
	//3���� �۾� ��� ���� ����
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
	//3D�ؽ�Ʈ ���
	HRESULT			DrawText3D();
	//���͸� �׸��� �Լ�
	void			DrawLine();
	//�α� �߰�
	//HRESULT		AddLog(LPTSTR _log, ...);
	//Ư�� �ε����� �α� �߰�
	HRESULT			AddLog(int _idx, LPTSTR _log, ...);
	//������ ��ġ(�������)�� �α� ���.enum���� ��ȣ ����
	HRESULT			AddStaticLog(int, LPTSTR , ...);
	//ȭ�鿡 3���� �ؽ�Ʈ ���(_isUpdate : ���ڿ��� �ٲ������ true)
	HRESULT			AddText3D(int, D3DXVECTOR3, LPTSTR, bool = false);
	//���� ����� ���� ���ڿ� ��ȯ
	HRESULT			VectorToString(LPTSTR dest, D3DXVECTOR3 vec);
	//����� ���� �߰�
	void			AddLine(D3DXVECTOR3, D3DXVECTOR3, D3DCOLOR );
	//��ǥ ��¿� ���� �߰�
	void			AddPosMark(D3DXVECTOR3, D3DCOLOR );
	//������� �ʱ�ȭ(���� �Լ� ���۽� �ʱ�ȭ)
	void			InitFaceCount();
	//������� �߰�(�׸������� ȣ��)
	void			AddFaceCount(UINT);

	void			ResetLine();

	void			ResetText3D();
	
private:
	CDebug(void);
	~CDebug(void);
};

