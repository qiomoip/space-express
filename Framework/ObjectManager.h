#pragma once
#include "Singleton.h"
/*
오브젝트 매니저
오브젝트를 관리하오...

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
	void					Init();
	void					Input();
	void					Update();
	void					CleanUp();
	HRESULT					Render();
	void					Collision();

public:
	CEntity*	FindObject(const string& strObjKey);

public:
	CEntity*			CreateEntity(const eMESH_TYPE& eMeshType, const eRENDER_TYPE& eRender, const string& strEntityKey, const eMESH_NUM& eMeshNum, const LPTSTR szMeshName = NULL);
	CEntity*			CreateEntity(const string& strEntityKey);

public:
	//비운 리스트에 비지블한 오브젝트만 삽입해줌.
	void Push_RenderList(CEntity* pEntity);
	void Remove_Object(CEntity*	pEntity);
	//렌더리스트 초기화함수(매 프레임마다 비우고 다시 채워놓는다.)
	void Reset_RenderList();
	//렌더리스트 반환
	list<CEntity*>* GetRenderList();
};

