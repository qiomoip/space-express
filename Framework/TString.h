#pragma once
#include "define.h"
/*
���ڿ� Ŭ����

�и� ��� �ʿ��� ���
tchar.h
windows.h
���ڿ� ����� �Է��Ҷ� _T��� _S�� ���
*/

class CTString
{
public:
	CTString(void);
	~CTString(void);
	
	void					Init();
	void					CleanUp();

	static LPTSTR			CharToTCHAR(LPSTR szStr);	//TCHAR�� char ���·�
	static LPSTR			TCHARToChar(LPTSTR szStr);	//char�� TCHAR ���·�
	
	//���ڿ� ����
	static HRESULT			Tstrcpy(LPTSTR dest, LPTSTR source);
	//���ڿ� ���̱�
	static HRESULT			Tstrcat(LPTSTR dest, LPTSTR source);
	//�������� ���ڿ� ���
	static LPTSTR			Tvprintf(LPTSTR str, ...);

	LPTSTR					GetStr();

	//���ڿ� ����� ���ڿ� ������ ��ȯ
	// _S("���ڿ�"); ���� ����ϸ� �� �Լ��� �ڵ����� ȣ���� �ش�.
	static LPTSTR			String( LPTSTR str);
	

	//������ �����ε�
	VOID					operator+=(LPTSTR source);
	VOID					operator+=(CTString* source);
	VOID					operator+=(D3DXVECTOR3 vector);

	LPTSTR					operator+(LPTSTR source1);
	//LPTSTR				operator+(D3DXVECTOR3 vector);
	CTString				operator+(CTString source1);
	CTString				operator+(D3DXVECTOR3 vector);
	VOID					operator=(LPTSTR source);
	
private:
	//�α�
	LPTSTR			m_String;
};


//_stprintf_s(std, _T("std %d"), 123);

//#define _T(_STR_)	{	LPTSTR Tstring = new TCHAR[255]; _tcscpy(Tstring, _tcslen(_STR_), _STR_); return _Tstring; }
#define _S(_STR_)	CTString::String(_T(_STR_))

