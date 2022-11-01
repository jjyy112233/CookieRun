#include "CustomSceneMgr.h"
#include "../../Ui/Custom/LeftUi.h"
#include "../../Ui/Custom/UderUi.h"
#include "../../Ui/Custom/CustomPage.h"
#include "../../Framework/ResourceManager.h"
#include "../../Framework/Framework.h"
#include "../../Framework/InputMgr.h"
#include "../../Framework/info.h"
#include "../../Scens/SceneManager.h"
#include "../../GameObject/SpriteObject.h"
#include "UnderObject.h"
#include "../../Framework/FileManager.h"

CustomSceneMgr::CustomSceneMgr(Scene* scene)
	:UiMgr(scene)
{
}

CustomSceneMgr::~CustomSceneMgr()
{
	Release();
}

void CustomSceneMgr::SetPage(string id)
{
	page->SetPage(id);
	under->SetPage(id);
}

void CustomSceneMgr::SetObj(string obj, bool isJelly)
{
	if (obj == "cursor")
	{
		page->SetObject("cursor", false);
		return;
	}
	page->SetObject(obj, isJelly);
	drawObj->SetTexture(*RESOURCES_MGR->GetTexture(obj));
	if (isJelly)
	{
		float h = drawObj->GetGlobalBound().height;
		drawObj->GetSprite()->GetSprite().setTextureRect({0,0,(int)h ,(int)h});
	}
	nowObj = obj;
}

void CustomSceneMgr::AddObj(Vector2f pos)
{
	if (page->GetState() == UiState::Down)
	{
		page->AddObj(pos);
	}
}

void CustomSceneMgr::Update(float dt)
{
	UiMgr::Update(dt);
	if (drawObj != nullptr)
	{
		Vector2f pos = SCENE_MGR->GetCurrScene()->ScreenToWorld((Vector2i)InputMgr::GetMousePos());

		if (drawPos.find(nowObj) != drawPos.end())
		{
			pos.y = drawPos[nowObj].y;
		}

		pos.x -= drawObj->GetGlobalBound().width / 2;
		drawObj->SetPos(pos);
	}
	if (InputMgr::GetKeyDown(Keyboard::F2))
	{
		Save();
	}
	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		nowObj = "graphics/Editor/erase.png";
		drawObj->SetTexture(*RESOURCES_MGR->GetTexture("graphics/Editor/erase.png"));
		drawObj->SetName("cursor");
		page->SetObject("cursor", false);
	}
}
void CustomSceneMgr::Save()
{
	auto saveData = page->GetData();
	

	FILE_MGR->SaveDataEpisode(saveData, GetName());
}

void CustomSceneMgr::Init()
{
	left = new LeftUi(this);
	left->SetButton(true);
	left->SetEpisode(GetName());
	left->SetPos({ 0,0 });
	left->Init();
	left->GetSprite()->SetTexture(*RESOURCES_MGR->GetTexture("graphics/Editor/leftUi.png"));
	left->GetSprite()->SetSize({ WINDOW_WIDTH * 0.1f,WINDOW_HEIGHT });

	under = new UderUi(this);
	under->SetButton(true);
	under->SetEpisode(GetName());
	under->SetPos({ (float)WINDOW_WIDTH * 0.1f, WINDOW_HEIGHT * 0.9f });
	under->Init();
	under->GetSprite()->SetTexture(*RESOURCES_MGR->GetTexture("graphics/Editor/underUi.png"));
	under->GetSprite()->SetSize({ WINDOW_WIDTH * 0.9f ,WINDOW_HEIGHT * 0.1f });

	page = new CustomPage();
	page->SetEpisode(GetName());
	page->Init();
	page->SetPage("stage1");
	page->GetSprite()->SetSize({ WINDOW_WIDTH ,WINDOW_HEIGHT });
	page -> SetBound(page->GetSprite()->GetGlobalBound());
	page->SetButton(false);

	uiObjList[1].push_back(page);
	uiObjList[1].push_back(left);
	uiObjList[1].push_back(under);
	drawObj = new UnderObject(this);
	drawObj->SetTexture(*RESOURCES_MGR->GetTexture("graphics/Editor/erase.png"));
	drawObj->SetName("cursor");
	page->SetObject("cursor", false);

	uiObjList[2].push_back(drawObj);

	drawPos = RESOURCES_MGR->GetEditorPos();
}
