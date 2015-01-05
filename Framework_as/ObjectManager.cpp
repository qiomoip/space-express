#include "ObjectManager.h"


CObjectManager::CObjectManager(void)
{
	m_Objects = new map<eTYPE, map<string, CEntity*>>;
}

CObjectManager::~CObjectManager(void)
{
}
