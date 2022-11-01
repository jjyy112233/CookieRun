#include "UderUi.h"
#include "../../Framework/FileManager.h"
#include "../../Framework/ResourceManager.h"
#include "../../Ui/Custom/UnderObject.h"
#include "../../GameObject/SpriteObject.h"	
#include "CustomSceneMgr.h"

UderUi::UderUi(CustomSceneMgr* mgr)
{
	sprite = new SpriteObject();
	this->mgr = mgr;
}

UderUi::~UderUi()
{
	Release();
}

void UderUi::SetPos(Vector2f pos)
{
	UiObject::SetPos(pos);
	sprite->SetPos(pos);
}

void UderUi::Init()
{
	SetBound(sprite->GetGlobalBound());
	mapData = FILE_MGR->GetEpisode(episodeId);
	int tmpX = 20.f;

	for (auto& Info : mapData)
	{
		Vector2f obj_pos = { position.x + 20 , position.y + 10 };

		UnderObject* obj = new UnderObject(mgr);
		obj->SetButton(true);
		obj->SetTexture(*RESOURCES_MGR->GetTexture(mapData[Info.first].bottomPath));
		obj->SetName(mapData[Info.first].bottomPath);
		float ratio = obj->GetGlobalBound().width / obj->GetGlobalBound().height;
		obj->SetSize({50* ratio, 50});
		obj->SetPos(obj_pos);
		obj_pos.x += obj->GetGlobalBound().width + tmpX;
		uiObjList[Info.first].push_back(obj);

		for (auto& o : Info.second.obstacles)
		{
			UnderObject* obj = new UnderObject(mgr);
			obj->SetButton(true);
			obj->SetTexture(*RESOURCES_MGR->GetTexture(o.first));
			obj->SetName(o.first);
			obj->SetScale({ 0.5f,0.5f });
			obj->SetPos(obj_pos);
			obj_pos.x += obj->GetGlobalBound().width + tmpX;

			obj->SetIsJelly(false);
			uiObjList[Info.first].push_back(obj);
		}
		for (auto& o : Info.second.jellys)
		{
			UnderObject* obj = new UnderObject(mgr);
			obj->SetButton(true);
			obj->SetTexture(*RESOURCES_MGR->GetTexture(o.first));
			obj->SetName(o.first);
			obj->SetScale({ 0.5f,0.5f });
			obj->SetPos(obj_pos);
			obj_pos.x += obj->GetGlobalBound().width + tmpX;
			obj->SetIsJelly(true);
			uiObjList[Info.first].push_back(obj);
		}
	}
	nowStage = &uiObjList.begin()->second;
	UiObject::Init();
}

void UderUi::Draw(RenderWindow& window)
{
	UiObject::Draw(window);
	sprite->Draw(window);
	for (auto& obj : *nowStage)
	{
		obj->Draw(window);
	}
}

void UderUi::Update(float dt)
{
	for (auto it = nowStage->rbegin(); it != nowStage->rend(); it++)
	{
		(*it)->Update(dt);
		if ((*it)->GetEvent())
			return;
	}
	UiObject::Update(dt);
	sprite->Update(dt);

}

void UderUi::SetPage(string id)
{
	nowStage = &(uiObjList[id]);
}

void UderUi::Release()
{
	for (auto& obj : uiObjList)
	{
		for(auto& o : obj.second)
			delete o;
		obj.second.clear();
	}
	uiObjList.clear();
	nowStage = nullptr;

	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}
