#pragma once
#include "define.h"
#include <memory>
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
	CTString(LPTSTR str);
	~CTString(void);
	
	void					Init();
	void					CleanUp();

	static shared_ptr<TCHAR>	CharToTCHAR(LPSTR szStr);	//TCHAR�� char ���·�
	static LPSTR				TCHARToChar(LPTSTR szStr);	//char�� TCHAR ���·�
	
	//���ڿ� ����
	static HRESULT				Tstrcpy(LPTSTR dest, LPTSTR source);
	//���ڿ� ���̱�
	static HRESULT				Tstrcat(LPTSTR dest, LPTSTR source);
	//�������� ���ڿ� ���
	static shared_ptr<TCHAR>	Tvprintf(LPTSTR str, ...);

	shared_ptr<TCHAR>			GetStr();

	//���ڿ� ����� ���ڿ� ������ ��ȯ
	// _S("���ڿ�"); ���� ����ϸ� �� �Լ��� �ڵ����� ȣ���� �ش�.
	//static LPTSTR			String( LPTSTR str);
	

	//������ �����ε�
	VOID						operator+=(LPTSTR source);
	VOID						operator+=(CTString* source);
	VOID						operator+=(D3DXVECTOR3 vector);

	shared_ptr<TCHAR>			operator+(LPTSTR source1);
	shared_ptr<TCHAR>			operator+(CTString* source1);
	shared_ptr<TCHAR>			operator+(D3DXVECTOR3 vector);
	VOID						operator=(LPTSTR source);
	
private:
	//�α�
	shared_ptr<TCHAR>		m_String;
};


//_stprintf_s(std, _T("std %d"), 123);

#define _S(_STR_)	CTString::String(_T(_STR_))

