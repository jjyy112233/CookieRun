#include "MenuUiMgr.h"
#include "../../Scens/Scene.h"
#include "MenuButton.h"
#include "../../GameObject/SpriteObject.h"
#include "../../GameObject/TextObject.h"
#include "../../Framework/ResourceManager.h"
#include "../../Framework/info.h"
#include "../../Scens/SceneManager.h"

MenuUiMgr::MenuUiMgr(Scene* scene)
	:UiMgr(scene)
{

}

void MenuUiMgr::Update(float dt)
{
	UiMgr::Update(dt);
}

void MenuUiMgr::Init()
{
	startBtn = new MenuButton(this);
	SpriteObject* btnSprite =  startBtn->GetSprite();
	btnSprite->SetTexture(*RESOURCES_MGR->GetTexture("graphics/ui2.png"));
	btnSprite->SetPos(Vector2f{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	btnSprite->SetOrigin(Origins::MC);
	startBtn->SetBound(btnSprite->GetGlobalBound());
	uiObjList[0].push_back(startBtn);
}

void MenuUiMgr::Release()
{
	UiMgr::Release();
}

void MenuUiMgr::Reset()
{
}

void MenuUiMgr::ClickStartBtn()
{
	SCENE_MGR->ChangeScene(Scenes::Ready);
}
