#include "ObjectManager.h"


CObjectManager::CObjectManager(void)
{
	Init();
}

CObjectManager::~CObjectManager(void)
{
	CleanUp();
}

void CObjectManager::Init()
{
	m_Objects = new map<eTYPE, map<LPTSTR, CEntity*>>;

	
#ifdef _DEBUG
	m_Info = new CInfo();
#endif
}

void CObjectManager::CleanUp()
{

#ifdef _DEBUG
	SAFE_DELETE(m_Info );
#endif
}