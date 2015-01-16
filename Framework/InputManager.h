#pragma once
#include "Singleton.h"

class CInputManager : public CSingleton<CInputManager>
{
private:
	friend CSingleton;

	CInputManager(void);
	~CInputManager(void);

	map<eKEY_NAME, KEY_INFO*>*		m_mapKey;
public:
	//초기화
	void						Init();
	void						CleanUp();
	//키 설정 변경
	HRESULT						SetKeycode(eKEY_NAME _keyName, int _keyCode);
	//키 입력상태 갱신
	HRESULT						UpdateKeyInput();
	//특정 키의 상태 반환
	bool						GetKeyInput(eKEY_NAME _keyName);
	
	eKEY_NAME					GetKeyInfo();

#ifdef _DEBUG
private:	
	CInfo*									m_Info;
#endif
};

