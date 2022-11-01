#include "LeftUi.h"
#include "../../Framework/FileManager.h"
#include "../../Framework/ResourceManager.h"
#include "../../Ui/Custom/LeftObject.h"
#include "../../GameObject/SpriteObject.h"	
#include "CustomSceneMgr.h";

LeftUi::LeftUi(CustomSceneMgr* mgr)
{
	sprite = new SpriteObject();
	this->mgr = mgr;
}

LeftUi::~LeftUi()
{
	Release();
}

void LeftUi::Release()
{
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
	for (auto& o : uiObjList)
	{
		delete o.second;
		o.second = nullptr;
	}
	uiObjList.clear();
}

void LeftUi::Update(float dt)
{
	UiObject::Update(dt);
	for (auto& obj : uiObjList)
	{
		obj.second->Update(dt);
	}
}

void LeftUi::Draw(RenderWindow& window)
{
	UiObject::Draw(window);
	sprite->Draw(window);
	for (auto& obj : uiObjList)
	{
		obj.second->Draw(window);
	}
}

void LeftUi::SetPos(Vector2f pos)
{
	sprite->SetPos(pos);
	UiObject::SetPos(pos);
}

void LeftUi::Init()
{
	SetBound(sprite->GetGlobalBound());
	mapData = FILE_MGR->GetEpisode(episodeId);
	int tmpY = 20.f;
	Vector2f obj_pos = { position.x+20, position.y+20 };
	for (auto& Info : mapData)
	{
		string stage = Info.first;
		string back = Info.second.backInfo[0].path;

		LeftObject* obj = new LeftObject(mgr);
		obj->SetId(stage);
		obj->SetTexture(*RESOURCES_MGR->GetTexture(back));
		obj->SetScale({ 0.1f,0.1f });
		obj->SetPos(obj_pos);
		obj_pos.y += obj->GetGlobalBound().width + tmpY;
		uiObjList[Info.first] = obj;
	}
	//nowStage = &uiObjList.begin()->second;
	UiObject::Init();
}
