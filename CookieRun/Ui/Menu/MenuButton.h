#pragma once
#include "../Button.h"

class SpriteObject;
class MenuUiMgr;
class MenuButton : public Button
{
private:
	SpriteObject* sprite;
	MenuUiMgr* mgr;

public:
	MenuButton(MenuUiMgr* mgr);
	SpriteObject* GetSprite() { return sprite; }
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

