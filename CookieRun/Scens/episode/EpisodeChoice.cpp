#include "EpisodeChoice.h"
#include "../../Ui/Ready/EpisodeBtn.h"
#include "../../GameObject/SpriteObject.h"
#include "../../GameObject/TextObject.h"
#include "../../Framework/ResourceManager.h"
#include "../../Framework/info.h"
#include "../../Framework/InputMgr.h"
#include "../SceneManager.h"

EpisodeChoice::EpisodeChoice()
	:Scene(Scenes::EpisodeList)
{
}

void EpisodeChoice::Enter()
{
	SetViewStop();
	Init();
}

void EpisodeChoice::Exit()
{
	Release();
}

void EpisodeChoice::Init()
{
	
	auto mapData = FILE_MGR->GetAllEpisode();

	float x = 250;
	float y = 150;

	for (auto& epi : mapData)
	{
		EpisodeBtn* btn = new EpisodeBtn(epi.first);

		btn->GetSprite()->SetTexture(*RESOURCES_MGR->GetTexture("graphics/ui5.png"));
		btn->GetSprite()->SetOrigin(Origins::MC);

		btn->GetText()->SetText(*RESOURCES_MGR->GetFont("fonts/CookieRun Bold.ttf"), 50, Color::White, epi.first);
		btn->GetText()->SetOrigin(Origins::MC);

		btn->SetPos(Vector2f{ x,y });
		btn->SetBound(btn->GetSprite()->GetGlobalBound());

		cout << btn->GetSprite()->GetGlobalBound().left << endl;
		cout << btn->GetSprite()->GetGlobalBound().top << endl;
		cout << btn->GetSprite()->GetGlobalBound().width << endl;
		cout << btn->GetSprite()->GetGlobalBound().height << endl;
		objList[LayerType::Bottom][0].push_back(btn);
		y += 250;
	}


}

void EpisodeChoice::Release()
{
	Scene::Release();
}

void EpisodeChoice::Update(float dt)
{
	Scene::Update(dt);
	if (InputMgr::GetKeyDown(Keyboard::Tab))
	{
		SCENE_MGR->ChangeScene(Scenes::Ready);
		return;
	}
}

void EpisodeChoice::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}
