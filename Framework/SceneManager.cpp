#include "SceneManager.h"
#include "Scene.h"
#include "EditorScene.h"
#include "MainGameScene.h"
#include "InitScene.h"

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
	m_pCurScene->Render();
	if(m_pCurScene->GetChange())
	{
		ChangeScene();
	}
}

void CSceneManager::Input()
{
	m_pCurScene->Input();
}

void CSceneManager::CreateScene(const eSCENE_TYPE& eScene)
{
	CScene* pScene = NULL;
	switch(eScene)
	{
	case STYPE_INIT:
		pScene = new CInitScene;
		break;
	case STYPE_EDIT:
		pScene = new CEditorScene;
		break;
	case STYPE_MAIN1:
		pScene = new CMainGameScene;
		break;
	}
	if(FAILED(pScene->Init()))
	{
		Safe_Delete(pScene);
		return;
	}

	if(m_pCurScene)
	{
		Safe_Delete(m_pCurScene);
		m_pCurScene = pScene;
	}
	else
	{
		m_pCurScene = pScene;
	}
}

void CSceneManager::PushScene(CScene* pScene)
{
	if(!m_pCurScene)
	{
		m_pCurScene = pScene;
	}
	else
		m_pNextScene = pScene;
}

void CSceneManager::ChangeScene()
{
	Safe_Delete(m_pCurScene);

	CScene* pScene = NULL;
	switch(m_eNextScene)
	{
	case STYPE_INIT:
		pScene = new CInitScene;
		break;
	case STYPE_EDIT:
		pScene = new CEditorScene;
		break;
	case STYPE_MAIN1:
		pScene = new CMainGameScene;
		break;
	}
	if(FAILED(pScene->Init()))
	{
		Safe_Delete(pScene);
		return;
	}

	m_pCurScene = pScene;
	m_pNextScene = NULL;
}

void CSceneManager::PushScene(const eSCENE_TYPE& eScene)
{
	if(m_pCurScene)
	{
		//m_pNextScene = pScene;
		m_eNextScene = eScene;
	}
	else
	{
		CScene* pScene = NULL;
		switch(eScene)
		{
		case STYPE_INIT:
			pScene = new CInitScene;
			break;
		case STYPE_EDIT:
			pScene = new CEditorScene;
			break;
		case STYPE_MAIN1:
			pScene = new CMainGameScene;
			break;
		}
		if(FAILED(pScene->Init()))
		{
			Safe_Delete(pScene);
			return;
		}

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