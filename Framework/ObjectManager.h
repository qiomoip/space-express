#pragma once
#include "Singleton.h"
/*
������Ʈ �Ŵ���
������Ʈ�� �����Ͽ�...

*/

class CEntity;

class CObjectManager : public CSingleton<CObjectManager>
{
private:
	friend CSingleton;
	CObjectManager(void);
	~CObjectManager(void);
	
	map<string, CEntity*>	m_mapObject;
	list<CEntity*>			m_listRenderList[RTYPE_MAX];

public:
	void								Init();
	void								Update();
	void								CleanUp();
	HRESULT								Render();

public:
	CEntity*			CreateEntity(const eMESH_TYPE& eMeshType, const eRENDER_TYPE& eRender, const string& strMeshKey, const LPTSTR szMeshName = NULL);
	CEntity*			CreateEntity(const string& strEntityKey);

public:
	void Push_RenderList(CEntity* pEntity);
	
};

