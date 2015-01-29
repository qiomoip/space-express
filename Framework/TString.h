#pragma once
#include "Singleton.h"

class CTString
	: public CSingleton<CTString>
{
	friend CSingleton;

public:
	LPTSTR	CharToTCHAR(LPSTR szStr);	//TCHAR�� char ���·�
	LPSTR	TCHARToChar(LPTSTR szStr);	//char�� TCHAR ���·�

private:
	CTString(void);
	~CTString(void);
};

