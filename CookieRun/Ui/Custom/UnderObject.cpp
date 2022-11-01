#include "UnderObject.h"
#include "../../GameObject/SpriteObject.h"
#include "CustomSceneMgr.h"
#include <iostream>

UnderObject::UnderObject(CustomSceneMgr* mgr)
{
	sprite = new SpriteObject();
	this->mgr = mgr;
}

UnderObject::~UnderObject()
{
	Release();
}

void UnderObject::SetTexture(Texture& tex)
{
	sprite->SetTexture(tex);
	SetBound(sprite->GetGlobalBound());
}

void UnderObject::SetPos(Vector2f pos)
{
	sprite->SetPos(pos);
	Button::SetPos(pos);
	SetBound(sprite->GetGlobalBound());
}

void UnderObject::SetSize(Vector2f pos)
{
	sprite->SetSize(pos);
	SetBound(sprite->GetGlobalBound());
}

void UnderObject::SetScale(Vector2f scale)
{
	sprite->SetScale(scale);
	SetBound(sprite->GetGlobalBound());
}


void UnderObject::Init()
{
	Button::Init();
}

void UnderObject::Reset()
{
	Button::Reset();
}

void UnderObject::Update(float dt)
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
		if (GetName() != "cursor")
		{
			sprite->SetColor(Color(200, 200, 200, 255));
			mgr->SetObj(GetName(), isJelly);
		}
		else
		{
			mgr->AddObj(GetPos());
		}
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


void UnderObject::Draw(RenderWindow& window)
{
	sprite->Draw(window);
	Button::Draw(window);
}

FloatRect UnderObject::GetGlobalBound()
{
	return sprite->GetGlobalBound();
}
FloatRect UnderObject::GetLocalBound()
{
	return sprite->GetGlobalBound();
}
