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
	m_Objects = new map<eTYPE, map<string, CEntity*>>;
}

void CObjectManager::CleanUp()
{

}