#pragma once
#include "define.h"

class CEntity;
class CLight;

class CScene
{
protected:
	LPDIRECT3DDEVICE9	m_pDevice;
	list<CEntity*>	m_RenderList;
	vector<CLight*>		m_vecLight;
	bool			m_bChangeScene;

public:
	virtual HRESULT Init();
	virtual void Update(){};
	void Render();
	virtual void Destroy();
	virtual void Input(){};

public:
	virtual HRESULT CreateEntity()PURE;
	virtual HRESULT CreateCamera()PURE;
	virtual HRESULT CreateLight()PURE;

public:
	void IsChange(const bool& bChange = true){m_bChangeScene = bChange;};
	const bool& GetChange() const {return m_bChangeScene;};
	
public:
	CScene(void);
	virtual ~CScene(void);
};

