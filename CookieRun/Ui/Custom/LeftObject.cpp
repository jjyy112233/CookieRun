#include "LeftObject.h"
#include "../../GameObject/SpriteObject.h"
#include "CustomSceneMgr.h"
#include <iostream>

LeftObject::LeftObject(CustomSceneMgr* mgr)
{
    sprite = new SpriteObject();
	this->mgr = mgr;
}

LeftObject::~LeftObject()
{
	Release();
}

void LeftObject::SetTexture(Texture& tex)
{
    sprite->SetTexture(tex);
    SetBound(sprite->GetGlobalBound());
}

void LeftObject::SetPos(Vector2f pos)
{
    sprite->SetPos(pos);
    SetBound(sprite->GetGlobalBound());
}

void LeftObject::SetSize(Vector2f size)
{
    sprite->SetSize(size);
    SetBound(sprite->GetGlobalBound());
}

void LeftObject::SetScale(Vector2f scale)
{
    sprite->SetScale(scale);
    SetBound(sprite->GetGlobalBound());
}

void LeftObject::Init()
{
    Button::Init();
}

void LeftObject::Reset()
{
    Button::Reset();
}

void LeftObject::Update(float dt)
{
	Button::Update(dt);
	switch (btnState)
	{
	case UiState::None:
		break;
	case UiState::Enter:
		break;
	case UiState::Stay:
		break;
	case UiState::Down:
		sprite->SetColor(Color(200, 200, 200, 255));
		isClick();
		break;
	case UiState::Up:
		sprite->SetColor(Color::White);
		break;
	case UiState::Exit:
		sprite->SetColor(Color::White);
		break;
	default:
		break;
	}
}

void LeftObject::Draw(RenderWindow& window)
{
	sprite->Draw(window);
	Button::Draw(window);
}

FloatRect LeftObject::GetGlobalBound()
{
	return sprite->GetGlobalBound();
}

FloatRect LeftObject::GetLocalBound()
{
	return sprite->GetGlobalBound();
}

bool LeftObject::isClick()
{
	mgr->SetPage(this->id);
	return true;
}
