#include "SceneManager.h"
#include "Scene.h"


CSceneManager::CSceneManager(void)
	: m_pCurScene(NULL)
	, m_pNextScene(NULL)
{
}


CSceneManager::~CSceneManager(void)
{
	Destroy();
}

void CSceneManager::Update()
{

}

void CSceneManager::Render()
{

}

void CSceneManager::CreateScene(eSCENE_TYPE& eScene)
{
	CScene* pScene = NULL;
	switch(eScene)
	{
	case STYPE_LOGO:
		break;
	case STYPE_MAIN1:
		break;
	}
	if(m_pCurScene)
	{
		Safe_Delete(m_pCurScene);
		m_pCurScene = pScene;
	}
}

const CScene*	CSceneManager::GetCurrentScene() const
{
	return m_pCurScene;
}

void CSceneManager::Destroy()
{
	Safe_Delete(m_pCurScene);
	Safe_Delete(m_pNextScene);
}