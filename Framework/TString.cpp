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
			memset(szRet, 0, sizeof(char) * 256);
			int len = WideCharToMultiByte( CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL );	
			WideCharToMultiByte( CP_ACP, 0, szStr, -1, szRet, len, NULL, NULL );

	return szRet;
}