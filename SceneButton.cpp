#include "SceneButton.h"
#include "SceneManager.h"
#include "Scene.h"

CSceneButton::CSceneButton(void)
	: m_eScene(STYPE_NULL)
	, m_pScene(NULL)
{
}


CSceneButton::~CSceneButton(void)
{
}

void CSceneButton::Initialize()
{
	CEntity::Initialize();
}

void CSceneButton::Update()
{
	CEntity::Update();
}

void CSceneButton::Schedule()
{
	_SINGLE(CSceneManager)->PushScene(m_eScene);
	m_pScene->IsChange();
}

void CSceneButton::SetSceneType(const eSCENE_TYPE& eType)
{
	m_eScene = eType;
}

void CSceneButton::SetScene(CScene* pScene)
{
	m_pScene = pScene;
}