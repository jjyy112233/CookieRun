#include "EditorChoice.h"
#include "../../Ui/Custom/EditorBtn.h"
#include "../../GameObject/SpriteObject.h"
#include "../../GameObject/TextObject.h"
#include "../../Framework/ResourceManager.h"
#include "../../Framework/info.h"
#include "../../Framework/InputMgr.h"
#include "../SceneManager.h"

EditorChoice::EditorChoice()
	:Scene(Scenes::EpisodeList)
{
}

void EditorChoice::Enter()
{
	SetViewStop();
	Init();
}

void EditorChoice::Exit()
{
	Release();
}

void EditorChoice::Init()
{
	
	auto mapData = FILE_MGR->GetAllEpisode();

	float x = 250;
	float y = 150;

	for (auto& epi : mapData)
	{
		EditorBtn* btn = new EditorBtn(epi.first);
		btn->GetSprite()->SetTexture(*RESOURCES_MGR->GetTexture("graphics/ui5.png"));
		btn->GetText()->SetText(*RESOURCES_MGR->GetFont("fonts/CookieRun Bold.ttf"), 50, Color::White, epi.first);
		btn->GetSprite()->SetOrigin(Origins::MC);
		btn->GetText()->SetOrigin(Origins::MC);
		btn->SetBound(btn->GetSprite()->GetGlobalBound());
		btn->SetPos(Vector2f{ x,y });
		objList[LayerType::Bottom][0].push_back(btn);
		y += 250;
	}


}

void EditorChoice::Release()
{
	Scene::Release();
}

void EditorChoice::Update(float dt)
{
	Scene::Update(dt);
	if (InputMgr::GetKeyDown(Keyboard::Tab))
	{
		SCENE_MGR->ChangeScene(Scenes::Ready);
		return;
	}
}

void EditorChoice::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}
