#include "GameEnd.h"
#include "../../GameObject/SpriteObject.h"
#include "../../GameObject/TextObject.h"
#include "GameEndButton.h"
#include "../../Framework/ResourceManager.h"
#include "../../Scens/Scene.h"
#include "../../Scens/SceneManager.h"
#include "../../Scens/episode/Episode.h"

void GameEnd::Init()
{
	isClick = false;
	UiObject::Init();
	back = new SpriteObject();
	back->SetTexture(*RESOURCES_MGR->GetTexture("graphics/ui6.png"));
	back->Init();
	back->SetOrigin(Origins::MC);
	back->SetPos(SCENE_MGR->GetCurrScene()->GetWorldView().getCenter());

	//retry = new GameEndButton();
	//retry->Set(Scenes::Episode, (Episode*)(SCENE_MGR->GetCurrScene()));
	//retry->Init();
	//Utils::SetOrigin(retry->GetSprite()->GetSprite(), Origins::MC);
	//retry->SetPos(back->GetPos() + Vector2f{-100.f, -100.f});
	//retry->SetGameEnd(this);

	epiList = new GameEndButton();
	epiList->Set(Scenes::EpisodeList, (Episode*)(SCENE_MGR->GetCurrScene()));
	epiList->Init();
	Utils::SetOrigin(epiList->GetSprite()->GetSprite(), Origins::MC);
	epiList->SetPos(back->GetPos() + Vector2f{ 0, -100.f });
	epiList->SetGameEnd(this);

	txt = new TextObject();
	txt->SetOrigin(Origins::MC);
	txt->SetText(*RESOURCES_MGR->GetFont("fonts/CookieRun Bold.ttf"), 50, Color::Yellow, "000");
	txt->SetPosition(back->GetPos() + Vector2f{ 0,100 });
	txt->Init();
}

void GameEnd::Release()
{
	//delete back;
	//back = nullptr;
	//delete txt;
	//txt = nullptr;
	//delete retry;
	//retry = nullptr;
	//delete epiList;
	//epiList = nullptr;
}

void GameEnd::Update(float dt)
{
	if (enabled)
	{
		UiObject::Update(dt);
		txt->Update(dt);
		back->Update(dt);
		//retry->Update(dt);
		epiList->Update(dt);
	}
	if (isClick)
		((Episode*)SCENE_MGR)->SetScene(nextScene);
}

void GameEnd::Draw(RenderWindow& window)
{
	if (enabled)
	{
		UiObject::Draw(window);
		back->Draw(window);
		//retry->Draw(window);
		epiList->Draw(window);
		txt->Draw(window);
	}

}

void GameEnd::SetScene(Scenes scene)
{
	nextScene = scene;
	isClick = true; 
}

void GameEnd::SetPoint(string str)
{
	txt->SetString(str);
	txt->SetOrigin(Origins::MC);
}
