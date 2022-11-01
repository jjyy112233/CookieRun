#pragma once
#include "../../Ui/UiObject.h"

struct MapData;
class Button;
class SpriteObject;
class CustomSceneMgr;
class UderUi : public UiObject
{
private:
	string episodeId;
	SpriteObject* sprite;
	map<string, MapData> mapData;

	map<string , vector<Button*>> uiObjList;
	vector<Button*>* nowStage;
	CustomSceneMgr* mgr;

public:
	UderUi(CustomSceneMgr* mgr);
	~UderUi();
	virtual void SetEpisode(string str) { episodeId = str; }
	virtual void SetPos(Vector2f pos);
	void Init() override;
	virtual void Draw(RenderWindow& window) override;
	virtual void Update(float dt) override;
	void SetPage(string id);
	virtual void Release() override;
	SpriteObject* GetSprite() { return sprite; }
};

