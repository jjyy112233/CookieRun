#include "CustomScene.h"
#include "../../Framework/InputMgr.h"
#include "../../GameObject/SpriteObject.h"
#include "../../Framework/Framework.h"
#include "../../Framework/info.h"
#include "../SceneManager.h"
#include "../../Ui/Custom/CustomSceneMgr.h"

CustomScene::CustomScene()
	:Scene(Scenes::Editor)
{
}

CustomScene::~CustomScene()
{
	Release();
}

void CustomScene::Update(float dt)
{
	Scene::Update(dt);
	//if (InputMgr::GetKeyDown(Keyboard::Space))
	//{
	//	FRAMEWORK->GetWindow().setSize({ 1920,1080 });
	//}
	//if (InputMgr::GetKeyDown(Keyboard::F1))
	//{
	//	FRAMEWORK->GetWindow().setSize({ 1280,720});
	//}
	if (InputMgr::GetKeyDown(Keyboard::Tab))
	{	
		SCENE_MGR->ChangeScene(Scenes::EditorList);
		return;
	}
}

void CustomScene::Enter()
{
	worldView.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	worldView.setCenter({ WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 });
	Init();
}

void CustomScene::Exit()
{
	Release();
}

void CustomScene::Init()
{
	uiMgr = new CustomSceneMgr(this);
	uiMgr->SetName(name);
	uiMgr->Init();
}

void CustomScene::Release()
{
	Scene::Release();
}
