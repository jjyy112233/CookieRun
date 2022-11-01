#include "MenuButton.h"
#include <iostream>
#include "../../GameObject/SpriteObject.h"
#include "MenuUiMgr.h"

MenuButton::MenuButton(MenuUiMgr* mgr)
	:mgr(mgr)
{
	SetButton(true);
	sprite = new SpriteObject();
}

void MenuButton::Update(float dt)
{
	Button::Update(dt);
	//std::cout << (int)btnState << std::endl;
	if(IsDown())
	{
		mgr->ClickStartBtn();
	}
}

void MenuButton::Draw(RenderWindow& window)
{
	sprite->Draw(window);
}
