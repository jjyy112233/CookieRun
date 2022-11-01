#include "CustonPageObject.h"
#include "../../GameObject/SpriteObject.h"
#include "CustomSceneMgr.h"
#include "../Button.h"
#include <iostream>
#include "CustomPage.h"
#include "../../Framework/InputMgr.h"

CustonPageObject::CustonPageObject()
{
	sprite = new SpriteObject();
}

CustonPageObject::~CustonPageObject()
{
	Release();
}

void CustonPageObject::SetTexture(Texture& tex)
{
	sprite->SetTexture(tex);
	SetBound(sprite->GetGlobalBound());
}

void CustonPageObject::SetPos(const Vector2f& pos)
{
	sprite->SetPos(pos);
	SetBound(sprite->GetGlobalBound());
	UiObject::SetPos(pos);
}

void CustonPageObject::Translate(const Vector2f& delta)
{
	sprite->SetPos(position + delta);
	UiObject::Translate(delta);
}

void CustonPageObject::SetSize(Vector2f size)
{
	sprite->SetSize(size);
	SetBound(sprite->GetGlobalBound());
}

void CustonPageObject::SetScale(Vector2f scale)
{
	sprite->SetScale(scale);
	SetBound(sprite->GetGlobalBound());
}

FloatRect CustonPageObject::GetGlobalBound()
{
	return sprite->GetGlobalBound();
}

void CustonPageObject::Init()
{
	UiObject::Init();
}

void CustonPageObject::Reset()
{
	UiObject::Reset();
}

void CustonPageObject::Update(float dt)
{
	UiObject::Update(dt);
	switch (btnState)
	{
	case UiState::None:
		break;
	case UiState::Enter:
		break;
	case UiState::Stay:
		break;
	case UiState::Down:
		if (InputMgr::GetMousePos().y > 648)
			return;
		
		page->DeleteObj(this);
		break;
	case UiState::Up:
		break;
	case UiState::Exit:
		break;
	default:
		break;
	}
}

void CustonPageObject::Draw(RenderWindow& window)
{
	sprite->Draw(window);
	UiObject::Draw(window);
}

FloatRect CustonPageObject::GetLocalBound()
{
	return sprite->GetGlobalBound();
}

bool CustonPageObject::isClick()
{
	
	return true;
}

void CustonPageObject::SetPage(CustomPage* page)
{
	this->page = page;
}

void CustonPageObject::Release()
{
	delete sprite;
}
