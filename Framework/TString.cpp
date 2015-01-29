#include "TString.h"


CTString::CTString(void)
{
}


CTString::~CTString(void)
{
}

LPTSTR	CTString::CharToTCHAR(LPSTR szStr)
{
	LPTSTR szRet = new TCHAR[256];

	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, strlen(szStr) + 1,
		szRet, _tcslen(szRet) + 1);

	return szRet;
}

LPSTR	CTString::TCHARToChar(LPTSTR szStr)
{
	LPSTR szRet = new CHAR[256];

	WideCharToMultiByte(CP_ACP, MB_PRECOMPOSED, szStr, _tcslen(szStr) + 1,
		szRet, strlen(szRet) + 1 , NULL, NULL);

	return szRet;
}