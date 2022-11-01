#include "UiObject.h"
#include "../../Framework/ResourceManager.h"
#include "../../Framework//InputMgr.h"
#include "../../Framework/Utils.h"

UiObject::UiObject() : btnState(UiState::None)
{
	isButton = true;
}

UiObject::~UiObject()
{
	Release();
}

void UiObject::Init()
{
	Reset();
	Object::Init();
}

void UiObject::Release()
{
	Object::Release();
}

void UiObject::Reset()
{
	btnState = UiState::None;
	isEvent = false;
	Object::Reset();
}

void UiObject::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	
}

void UiObject::Translate(const Vector2f& delta)
{
	Object::Translate(delta);
}

void UiObject::Update(float dt)
{
	auto mousePos = InputMgr::GetMousePos();
	auto btnBoudn = bound;

	switch (btnState)
	{
	case UiState::None:
		if (Utils::IsRange(btnBoudn, mousePos))
		{
			btnState = UiState::Enter;
			isEvent = true;
		}
		break;
	case UiState::Enter:
		if (!Utils::IsRange(btnBoudn, mousePos))
		{
			btnState = UiState::Exit;
			isEvent = true;
		}
		else if (InputMgr::GetMouseButtonDown(Mouse::Left))
		{
			btnState = UiState::Down;
			isEvent = true;
		}
		else if (InputMgr::GetMouseButtonUp(Mouse::Left))
		{
			btnState = UiState::Up;
			isEvent = true;
		}
		else
		{
			//PRINT("Stay");
		}
		break;
	case UiState::Down:
		if (Utils::IsRange(btnBoudn, mousePos))
		{
			btnState = UiState::Enter;
			isEvent = true;
		}
		else
		{
			btnState = UiState::None;
		}
		break;
	case UiState::Up:
		if (Utils::IsRange(btnBoudn, mousePos))
		{
			btnState = UiState::Enter;
			isEvent = true;
		}
		else
		{
			btnState = UiState::None;
		}
		break;
	case UiState::Exit:
		btnState = UiState::None;
		break;
	default:
		break;
	}
}

void UiObject::Draw(RenderWindow& window)
{
	isEvent = false;
}
