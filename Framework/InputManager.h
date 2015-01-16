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
	//�ʱ�ȭ
	void						Init();
	void						CleanUp();
	//Ű ���� ����
	HRESULT						SetKeycode(eKEY_NAME _keyName, int _keyCode);
	//Ű �Է»��� ����
	HRESULT						UpdateKeyInput();
	//Ư�� Ű�� ���� ��ȯ
	bool						GetKeyInput(eKEY_NAME _keyName);
	
	eKEY_NAME					GetKeyInfo();

#ifdef _DEBUG
private:	
	CInfo*									m_Info;
#endif
};

