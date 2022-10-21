#include "BackGround.h"
#include <iostream>
#include "../../Scens/SceneManager.h"

BackGround::BackGround(Texture* tex, float spd)
{
	SetTexture(*tex);
	width = (int)sprite.getGlobalBounds().width;
	height = (int)sprite.getGlobalBounds().height;
	speed = spd;

	right.SetTexture(*tex);
	right.SetPos({ (float)width, 0.f });

	right2.SetTexture(*tex);
	right2.SetPos({ (float) + width*2.f, 0.f});
}

void BackGround::Update(float dt)
{

	Translate(dt * speed * Vector2f{ -1.f,0.f });
	right.SetPos(Vector2f{ position.x + (float)width, 0.f });
	right2.SetPos(Vector2f{ position.x + (float)width*2.f, 0.f });

	auto worldPos = SCENE_MGR->GetCurrScene()->ScreenToWorld({0,0});

	if (worldPos.x > position.x + width)
	{
		std::cout << "OUT" << std::endl;
		SetPos(SCENE_MGR->GetCurrScene()->ScreenToWorld({ 0, 0 }));
	}
	SpriteObject::Update(dt);
}

void BackGround::Draw(RenderWindow& window)
{
	SpriteObject::Draw(window);
	right2.Draw(window);
	right.Draw(window);
}
	