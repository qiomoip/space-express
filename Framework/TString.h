#pragma once
#include "Singleton.h"

class CTString
	: public CSingleton<CTString>
{
	friend CSingleton;

public:
	LPTSTR	CharToTCHAR(LPSTR szStr);	//TCHAR을 char 형태로
	LPSTR	TCHARToChar(LPTSTR szStr);	//char을 TCHAR 형태로

private:
	CTString(void);
	~CTString(void);
};

