#include "SceneDev1.h"
#include "SceneMgr.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceManager.h"
#include "../GameObject/SpriteObject.h"
#include "../GameObject/TextObject.h"
#include "../Framework/SoundMgr.h"

SceneDev1::SceneDev1()
	:Scene(Scenes::Dev1)
{
	SpriteObject* obj = new SpriteObject();
	obj->SetTexture(*RESOURCES_MGR->GetTexture("graphics/player3.png"));
	objList.push_back(obj);
	
	TextObject* ui = new TextObject();
	ui->SetText(*RESOURCES_MGR->GetFont("fonts/NotoSansKR-Medium.otf"), 75, Color::White, "Dev1");
	uiObjList.push_back(ui);
	ui->SetOrigin(Origins::TR);
	ui->SetPosition(Vector2f{ 1280,0 });
}

SceneDev1::~SceneDev1()
{
}

void SceneDev1::Enter()
{
	
	SOUND_MGR->Play("sounds/gameSceneBgm.wav", true);
}

void SceneDev1::Exit()
{
}

void SceneDev1::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Key::Space))
		SCENE_MGR->ChangeScene(Scenes::Dev2);

	if (InputMgr::GetKeyDown(Keyboard::Key::Enter))
	{
		SOUND_MGR->Play("sounds/select.wav");
	}
	Scene::Update(dt);
}

void SceneDev1::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}
