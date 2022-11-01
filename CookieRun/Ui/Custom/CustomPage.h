#pragma once
#include "../../Ui/UiObject.h"

struct MapData;
class Button;
class SpriteObject;
class CustonPageObject;
class CustomPage : public UiObject
{
	string episodeId;
	string nowStage;
	string nowObj;
	SpriteObject* back;

	map<string, MapData> mapData;
	vector<bool> bottomState;
	map<int, vector<UiObject*>> uiObjList;
	float viewX;

	bool isJelly;
public:
	CustomPage();
	~CustomPage();
	virtual void SetEpisode(string str) { episodeId = str; }
	virtual void SetPos(Vector2f pos);
	void Init() override;
	virtual void Draw(RenderWindow& window) override;
	virtual void Update(float dt) override;
	void SetPage(string id);
	void SetObject(string id, bool isJelly);
	void AddObj(Vector2f pos);
	void SetBottom();
	void SetMapData(map<string, MapData> mapData) { this->mapData = mapData; }
	SpriteObject* GetSprite() { return back; }
	virtual void Release() override;
	map<string, MapData> GetData();
	void DeleteObj(UiObject* obj);
};

