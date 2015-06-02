#pragma once
#include "entity.h"
class CTiger :
	public CEntity
{
public:
	void Initialize();
	void Update();
	void Input();

public:
	CTiger(void);
	~CTiger(void);
};

