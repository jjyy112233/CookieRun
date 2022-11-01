#include "GameEndButton.h"
#include "../../GameObject/SpriteObject.h"
#include "../../Scens/episode/Episode.h"
#include "../../Framework/ResourceManager.h"
#include "../../Ui/Episode/GameEnd.h"

void GameEndButton::Set(Scenes scene, Episode* epi)
{
	this->epi = epi;
	this->scene = scene;
}

void GameEndButton::Init()
{
	Button::Init();
	btn = new SpriteObject();
	if (scene == Scenes::Episode)
	{
		btn->SetTexture(*RESOURCES_MGR->GetTexture("graphics/ui7.png"));
	}
	else
	{
		btn->SetTexture(*RESOURCES_MGR->GetTexture("graphics/ui8.png"));
	}

	SetBound(btn->GetGlobalBound());
}

void GameEndButton::Update(float dt)
{
	Button::Update(dt);;
	btn->Update(dt);
	if (IsEnter())
	{
		btn->SetColor(Color(200, 200, 200, 255));
	}
	if (IsExit())
	{
		btn->SetColor(Color(255, 255, 255, 255));
	}
	if (IsDown())
	{
		gameEnd->SetScene(scene);
	}
}

void GameEndButton::Draw(RenderWindow& window)
{
	Button::Draw(window);
	btn->Draw(window);
}

void GameEndButton::SetPos(Vector2f pos)
{
	Button::SetPos(pos);
	btn->SetPos(pos);
	SetBound(btn->GetGlobalBound());
}
