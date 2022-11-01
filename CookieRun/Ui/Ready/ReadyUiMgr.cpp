#include "ReadyUiMgr.h"
#include "../../Scens/Scene.h"
#include "ReadyButton.h"
#include "../../GameObject/SpriteObject.h"
#include "../../Framework/ResourceManager.h"
#include "../../Framework/info.h"
#include "../../Scens/SceneManager.h"

ReadyUiMgr::ReadyUiMgr(Scene* scene)
	:UiMgr(scene)
{

}

void ReadyUiMgr::Update(float dt)
{
	UiMgr::Update(dt);
}

void ReadyUiMgr::Init()
{
	episode = new ReadyButton(this);
	episode->SetName("Episode");
	SpriteObject* btnSprite = episode->GetSprite();

	btnSprite->SetTexture(*RESOURCES_MGR->GetTexture("graphics/ui3.png"));
	btnSprite->SetOrigin(Origins::MC);
	btnSprite->SetPos(Vector2f{ WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT / 2 });
	episode->SetBound(btnSprite->GetGlobalBound());
	uiObjList[0].push_back(episode);

	editor = new ReadyButton(this);
	editor->SetName("Editor");
	btnSprite = editor->GetSprite();

	btnSprite->SetTexture(*RESOURCES_MGR->GetTexture("graphics/ui4.png"));
	btnSprite->SetOrigin(Origins::MC);
	btnSprite->SetPos(Vector2f{ WINDOW_WIDTH / 2 -300, WINDOW_HEIGHT / 2 });
	editor->SetBound(btnSprite->GetGlobalBound());
	uiObjList[0].push_back(editor);
}

void ReadyUiMgr::Release()
{
}

void ReadyUiMgr::Reset()
{
}

void ReadyUiMgr::ClickEpisodeBtn()
{
	SCENE_MGR->ChangeScene(Scenes::EpisodeList);
}

void ReadyUiMgr::ClickEditortBtn()
{
	SCENE_MGR->ChangeScene(Scenes::EditorList);
}