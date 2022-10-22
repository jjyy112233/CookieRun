#include "BackGround.h"
#include <iostream>
#include "../../Scens/SceneManager.h"
#include "../../Framework/info.h"

BackGround::BackGround(Texture* tex, float spd)
{
	SetTexture(*tex);
	SetScale({ 2,2 });
	width = (int)sprite.getGlobalBounds().width;
	height = (int)sprite.getGlobalBounds().height;
	speed = spd;

	right.SetTexture(*tex);
	right.SetScale({ 2,2 });
	right.SetPos({ (float)width, 0.f });

	right2.SetTexture(*tex);
	right2.SetScale({ 2,2 });
	right2.SetPos({ (float) + width*2.f, 0.f});

	SetColor(Color::Black);
	right.SetColor(Color::Black);
	right2.SetColor(Color::Black);
	color = 0.f;

	state = BackState::None;
	timer = 0.f;

}

void BackGround::Update(float dt)
{
	if (enabled)
	{
		UpdateBackGround(dt);
		Translate(dt * speed * Vector2f{ -1.f,0.f });
		right.SetPos(Vector2f{ position.x + (float)width, 0.f });
		right2.SetPos(Vector2f{ position.x + (float)width * 2.f, 0.f });

		auto worldPos = SCENE_MGR->GetCurrScene()->ScreenToWorld({ 0,0 });

		if (worldPos.x > position.x + width)
		{
			std::cout << "OUT" << std::endl;
			SetPos(SCENE_MGR->GetCurrScene()->ScreenToWorld({ 0, 0 }));
		}
		SpriteObject::Update(dt);
	}
}
void BackGround::SetBackgroundState(BackGround::BackState s)
{
	state = s;
	switch (state)
	{
	case BackGround::BackState::None:
		break;
	case BackGround::BackState::Disable:
		color = 255.f;
		break;
	case BackGround::BackState::Enable:
		color = 0.f;
		break;
	default:
		break;
	}
}
void BackGround::UpdateBackGround(float dt)
{
	switch (state)
	{
	case BackGround::BackState::None:
		break;
	case BackGround::BackState::Disable:
		if (color >= 0)
		{
			color -= dt * 300;
			color = max(color, 0.f);
			SetColor(Color((int)color, (int)color, (int)color, (int)color));
			right.SetColor(Color((int)color, (int)color, (int)color, (int)color));
			right2.SetColor(Color((int)color, (int)color, (int)color, (int)color));
		}
		else
		{
			SetBackgroundState(BackState::None);
		}
		break;
	case BackGround::BackState::Enable:
		if (color < 255)
		{
			color += dt * 100;
			color = min(color, 255.f);
			SetColor(Color((int)color, (int)color, (int)color, (int)color));
			right.SetColor(Color((int)color, (int)color, (int)color, (int)color));
			right2.SetColor(Color((int)color, (int)color, (int)color, (int)color));
		}
		else
		{
			SetBackgroundState(BackState::None);
		}
		break;
	default:
		break;
	}
}
void BackGround::SetActive(bool active)
{
	SpriteObject::SetActive(active);
	right.SetActive(active);
	right2.SetActive(active);
}
void BackGround::Draw(RenderWindow& window)
{
	if (enabled)
	{
		SpriteObject::Draw(window);
		right2.Draw(window);
		right.Draw(window);
	}
}
	