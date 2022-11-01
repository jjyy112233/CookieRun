#include "Button.h"

Button::Button()
{
	enabled = true;
	btnState = UiState::None;
	Init();
}

void Button::SetClickFunc(bool(*isClick)())
{
	this->isClick = isClick;
}



Button::~Button()
{
}

void Button::Init()
{
	UiObject::Init();
}

void Button::Reset()
{
	UiObject::Reset();
}

void Button::Update(float dt)
{
	UiObject::Update(dt);
}

void Button::Draw(RenderWindow& window)
{
	UiObject::Draw(window);
}
