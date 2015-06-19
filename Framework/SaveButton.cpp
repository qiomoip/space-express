#include "SaveButton.h"
#include "ObjectManager.h"
#include "EditorScene.h"


CSaveButton::CSaveButton(void)
	: m_pScene(NULL)
{
}


CSaveButton::~CSaveButton(void)
{
}


void CSaveButton::Initialize()
{
	CEntity::Initialize();
}

void CSaveButton::Update()
{
	CEntity::Update();
}

void CSaveButton::Schedule()
{
	//오브젝트들의 아이디, 위치값, 스케일값, 트랜스값 등등을 저장한다
	
	//지금은 박스들의 위치값, 아이디만 저장하자 (스케일은 무조건 1)
	CreateDirectory(L"Data", NULL);
	
	HANDLE hFile = CreateFile(L"Data\\BoxPos.txt", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if(INVALID_HANDLE_VALUE == hFile)
			return;

	int iBoxCount = ((CEditorScene*)m_pScene)->GetBoxCount();

	DWORD dwBytes = 0;

	int* pCount = new int;
	*pCount = iBoxCount;

	WriteFile(hFile, pCount, sizeof(int), &dwBytes, NULL);

	for(int i = 0; i < iBoxCount; ++i)
	{
		string strName = "PickingBox";
		strName += i;

		//CEntity* pBox = _SINGLE(CObjectManager)->FindObject(strName);
		list<CEntity*> listBox = ((CEditorScene*)m_pScene)->GetBoxList();

		for(list<CEntity*>::iterator iter = listBox.begin(); iter != listBox.end(); ++iter)
		{
			const string* pName = &((*iter)->GetName());
			const D3DXVECTOR3* pPos = &((*iter)->GetPos());

			if(WriteFile(hFile, pName, sizeof(string), &dwBytes, NULL) == false)
			{
				CloseHandle(hFile);
				return;
			}
			if(WriteFile(hFile, pPos, sizeof(D3DXVECTOR3), &dwBytes, NULL) == false)
			{
				CloseHandle(hFile);
				return;
			}
		}

		

	}

	CloseHandle(hFile);
}

void CSaveButton::SetScene(CScene* pScene)
{
	m_pScene = pScene;
}