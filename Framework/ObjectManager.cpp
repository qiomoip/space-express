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
}

void CObjectManager::CleanUp()
{

}