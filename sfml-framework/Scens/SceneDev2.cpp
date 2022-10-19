#include "SceneDev2.h"
#include "SceneMgr.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceManager.h"
#include "../GameObject/SpriteObject.h"
#include "../GameObject/TextObject.h"
#include "../Framework/Utils.h"

SceneDev2::SceneDev2()
	:Scene(Scenes::Dev2)
{
	SpriteObject* obj = new SpriteObject();
	obj->SetTexture(*RESOURCES_MGR->GetTexture("graphics/player5.png"));
	objList.push_back(obj);

	TextObject* ui = new TextObject();
	ui->SetText(*RESOURCES_MGR->GetFont("fonts/NotoSansKR-Medium.otf"), 75, Color::White, "Dev2");
	ui->SetPos(Vector2f{});
	uiObjList.push_back(ui);
	ui->SetOrigin(Origins::TR);
	ui->SetPosition(Vector2f{ 1280,0 });
}

SceneDev2::~SceneDev2()
{
}

void SceneDev2::Enter()
{

}

void SceneDev2::Exit()
{
}

void SceneDev2::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Key::Space))
		SCENE_MGR->ChangeScene(Scenes::Dev1);
	Scene::Update(dt);
}

void SceneDev2::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}
