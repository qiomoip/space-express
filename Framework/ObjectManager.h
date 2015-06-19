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
	//��� ����Ʈ�� �������� ������Ʈ�� ��������.
	void Push_RenderList(CEntity* pEntity);
	void Remove_Object(CEntity*	pEntity);
	//��������Ʈ �ʱ�ȭ�Լ�(�� �����Ӹ��� ���� �ٽ� ä�����´�.)
	void Reset_RenderList();
	//��������Ʈ ��ȯ
	list<CEntity*>* GetRenderList();
};

