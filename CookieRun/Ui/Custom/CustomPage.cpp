#include "CustomPage.h"
#include "../../Framework/info.h"
#include "../../GameObject/SpriteObject.h"
#include "../../Framework/ResourceManager.h"
#include "../Button.h"
#include "CustonPageObject.h"
#include "../../Framework/InputMgr.h"
#include <algorithm>


CustomPage::CustomPage()
{
	back = new SpriteObject();
}

CustomPage::~CustomPage()
{
	Release();
}

void CustomPage::SetPos(Vector2f pos)
{
	UiObject::SetPos(pos);
	back->SetPos(pos);
}

void CustomPage::Init()
{
	mapData = FILE_MGR->GetEpisode(episodeId); 
	viewX = 0.f;
	isJelly = false;
}

void CustomPage::Draw(RenderWindow& window)
{
	UiObject::Draw(window);
	back->Draw(window);

	for (auto& obj : uiObjList)
	{
		for (auto& o : obj.second)
		{
			o->Draw(window);
		}
	}
}

void CustomPage::Update(float dt)
{
	back->Update(dt);
	UiObject::Update(dt);
	for (auto& obj : uiObjList)
	{
		for (auto& o : obj.second)
		{
			o->Update(dt);
		}
	}
	if (InputMgr::GetKey(Keyboard::A))
	{
		viewX -= dt * 500;
		for (auto& obj : uiObjList)
		{
			for (auto& o : obj.second)
			{
				o->Translate({ dt * 500,0 });
			}
		}
	}
	if (InputMgr::GetKey(Keyboard::D))
	{
		viewX += dt * 500;
		for (auto& obj : uiObjList)
		{
			for (auto& o : obj.second)
			{
				o->Translate({ -dt * 500,0 });
			}
		}
	}

}

void CustomPage::SetPage(string id)
{
	viewX = 0.f;
	back->SetTexture(*RESOURCES_MGR->GetTexture(mapData[id].backInfo[0].path));
	nowStage = id;

	auto bottomPath = mapData[nowStage].bottomPath;
	vector<int> bottom = mapData[nowStage].bottomPos;

	Vector2f pos = { 0, (WINDOW_HEIGHT - 100) };
	bool isDraw = true;


	for (auto& obj : uiObjList[1])
	{
		delete obj;
	}
	uiObjList[1].clear();
	for (auto& cnt : bottom)
	{
		for (int i = 0; i < cnt; i++)
		{
			if (isDraw)
			{
				CustonPageObject* c_block = new CustonPageObject();
				c_block->SetTexture(*RESOURCES_MGR->GetTexture(bottomPath));

				c_block->SetPos(pos);
				c_block->SetName("Bottom");
				uiObjList[1].push_back(c_block);
			}
			bottomState.push_back(isDraw);
			pos.x += 124;
		}
		isDraw = !isDraw;
	}

	auto objs = mapData[nowStage].obstacles;

	for (auto& obj : uiObjList[2])
	{
		delete obj;
	}
	uiObjList[2].clear();
	for (auto& obj : objs)
	{
		string path = obj.first;
		for (auto& o : obj.second)
		{
			CustonPageObject* c_obj = new CustonPageObject();
			c_obj->SetTexture(*RESOURCES_MGR->GetTexture(path));
			c_obj->SetPos(o);
			c_obj->SetPage(this);
			c_obj->SetName(path);
			c_obj->SetJelly(false);
			uiObjList[2].push_back(c_obj);
		}
	}

	auto jellys = mapData[nowStage].jellys;
	uiObjList[3].clear();
	for (auto& obj : jellys)
	{
		string path = obj.first;
		for (auto& o : obj.second)
		{
			CustonPageObject* c_obj = new CustonPageObject();
			c_obj->SetTexture(*RESOURCES_MGR->GetTexture(path));
			float h = c_obj->GetGlobalBound().height;
			c_obj->GetSprite()->GetSprite().setTextureRect({ 0,0,(int)h ,(int)h });
			c_obj->SetPos(o);
			c_obj->SetPage(this);
			c_obj->SetName(path);
			c_obj->SetJelly(true);
			uiObjList[3].push_back(c_obj);
		}
	}

	SetBottom();
}

void CustomPage::SetObject(string id, bool isJelly)
{
	nowObj = id;
	this->isJelly = isJelly;
}
void CustomPage::AddObj(Vector2f pos)
{
	if (InputMgr::GetMousePos().y > 648)
		return;
	if (nowObj == "cursor")
		return;
	CustonPageObject* c_obj = new CustonPageObject();
	c_obj->SetTexture(*RESOURCES_MGR->GetTexture(nowObj));
	if (isJelly)
	{
		float h = c_obj->GetGlobalBound().height;
		c_obj->GetSprite()->GetSprite().setTextureRect({ 0,0,(int)h ,(int)h });
		c_obj->SetJelly(true);
	}
	c_obj->SetPos(pos);
	c_obj->SetPage(this);
	c_obj->SetName(nowObj);

	if (!isJelly)
	{
		uiObjList[2].push_back(c_obj);

		pos.x += viewX;
		mapData[nowStage].obstacles[nowObj].push_back({ pos });
	}
	if (isJelly)
	{
		uiObjList[3].push_back(c_obj);

		pos.x += viewX;
		mapData[nowStage].jellys[nowObj].push_back({ pos });
	}
}

void CustomPage::SetBottom()
{
	for (auto bottom : bottomState)
	{
		//cout << bottom << endl;
	}
}

void CustomPage::Release()
{
	UiObject::Release();
	for (auto& obj : uiObjList)
	{
		for (auto& o : obj.second)
		{
			delete o;
		}
		obj.second.clear();
	}
	uiObjList.clear();
}

map<string, MapData> CustomPage::GetData()
{
	return mapData;
}


void CustomPage::DeleteObj(UiObject* obj)
{
	if (obj->GetName() == "Bottom")
		return;
	if (nowObj != "cursor")
		return;

	string objName = obj->GetName();
	bool isJ = ((CustonPageObject*)obj)->GetJelly();
	if (!isJ)
	{
		auto del = find(uiObjList[2].begin(), uiObjList[2].end(), obj);
		int n = del - uiObjList[2].begin();
		uiObjList[2].erase(del);

		int i = 0;
		for (auto& d : mapData[nowStage].obstacles)
		{
			int ii = 0;
			for (auto& d2 : d.second)
			{
				if (i == n)
				{
					mapData[nowStage].obstacles[objName].erase((mapData[nowStage].obstacles[objName].begin() + ii));
					delete obj;
					return;
				}
				i++;
				ii++;
			}
		}
	}
	else
	{
		auto del = find(uiObjList[3].begin(), uiObjList[3].end(), obj);
		int n = del - uiObjList[3].begin();
		uiObjList[3].erase(del);

		mapData[nowStage].jellys[objName].erase((mapData[nowStage].jellys[objName].begin() + n));
		delete obj;
		return;
	}
}

