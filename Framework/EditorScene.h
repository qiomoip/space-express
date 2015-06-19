#pragma once
#include "scene.h"
class CEntity;

class CEditorScene :
	public CScene
{
private:
	int	m_iBoxCnt;
	list<CEntity*>	m_listBox;

public:
	HRESULT Init();
	void Update();
	void Destroy();
	void Input();

public:
	HRESULT CreateEntity();
	HRESULT CreateCamera();
	HRESULT CreateLight();
	HRESULT CreateBox(LPCWSTR pFileName);

public:
	const int& GetBoxCount() const {return m_listBox.size();};//m_iBoxCnt;};
	const list<CEntity*>&	GetBoxList() const {return m_listBox;};

public:
	CEditorScene(void);
	virtual ~CEditorScene(void);
};

