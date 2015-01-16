#include "InputManager.h"
#include "define.h"

CInputManager::CInputManager(void) : m_mapKey(NULL)
{
	Init();
}


CInputManager::~CInputManager(void)
{
	CleanUp();
}

void CInputManager::Init()
{
	m_mapKey = new map<eKEY_NAME, KEY_INFO*>;
	m_mapKey->insert ( map<eKEY_NAME, KEY_INFO*>::value_type(KEY_RIGHT, new KEY_INFO(VK_RIGHT) ) );
	m_mapKey->insert ( map<eKEY_NAME, KEY_INFO*>::value_type(KEY_UP, new KEY_INFO(VK_UP) ) );
	m_mapKey->insert ( map<eKEY_NAME, KEY_INFO*>::value_type(KEY_LEFT, new KEY_INFO(VK_LEFT) ) );
	m_mapKey->insert ( map<eKEY_NAME, KEY_INFO*>::value_type(KEY_DOWN, new KEY_INFO(VK_DOWN) ) );
	m_mapKey->insert ( map<eKEY_NAME, KEY_INFO*>::value_type(KEY_ACTION, new KEY_INFO(VK_SPACE) ) );
	m_mapKey->insert ( map<eKEY_NAME, KEY_INFO*>::value_type(KEY_TURN_L, new KEY_INFO('Q') ) );
	m_mapKey->insert ( map<eKEY_NAME, KEY_INFO*>::value_type(KEY_TURN_R, new KEY_INFO('E') ) );
	
#ifdef _DEBUG
	m_Info = new CInfo();
#endif
}

void CInputManager::CleanUp()
{
	map<eKEY_NAME, KEY_INFO*>::iterator it = m_mapKey->begin();
	for(; it != m_mapKey->end(); ++it)
		SAFE_DELETE(it->second);
	m_mapKey->clear();
	SAFE_DELETE( m_mapKey );
		
#ifdef _DEBUG
	SAFE_DELETE(m_Info );
#endif
}

HRESULT CInputManager::SetKeycode(eKEY_NAME _keyName, int _keyCode)
{
	map<eKEY_NAME, KEY_INFO*>::iterator it_find = m_mapKey->find(_keyName) ;
	if( it_find != m_mapKey->end())
	{
		*(it_find->second) = _keyCode;
		return S_OK;
	}
	return S_FALSE;
}

HRESULT CInputManager::UpdateKeyInput()
{

	map<eKEY_NAME, KEY_INFO*>::iterator it = m_mapKey->begin();
	for(; it != m_mapKey->end(); ++it)
		//각 키마다 눌렸는지 체크후 isPressed에 반영.
			(it->second)->isPressed = GetAsyncKeyState( (it->second)->keyCode ) ? true : false;
	return S_FALSE;
}

bool	CInputManager::GetKeyInput(eKEY_NAME _keyName)
{	
	return m_mapKey->find(_keyName)->second->isPressed;
}

//
//LPTSTR*	CInputManager::GetKeyInfo()
//{
//	UINT	size = m_mapKey->size();
//	
//	LPTSTR* keyInfo = new LPTSTR[size];
//	map<LPTSTR, KEY_INFO*>::iterator it = m_mapKey->begin();
//	int  i = 0;
//
//	for(; it != m_mapKey->end(); ++it)
//	{
//		LPTSTR key = it->first;
//		keyInfo[i] = new TCHAR[_tcslen(key) + 10];
//		_tcscpy( keyInfo[i] , key );
//	}
//	return keyInfo;
//
//}