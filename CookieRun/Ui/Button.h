#pragma once
#include "UiObject.h"

class Button : public UiObject
{
protected:
public:
	Button();
	void SetClickFunc(bool (*isClick)());
	virtual ~Button();
	virtual void Init();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};

