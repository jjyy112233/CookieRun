#pragma once
#include "../../Ui/UiObject.h"

class SpriteObject;
class Button;
class CustomSceneMgr;
class LeftUi : public UiObject
{
private:
	string episodeId;
	SpriteObject* sprite;
	map<string, MapData> mapData;

	map<string, Button*> uiObjList;

	CustomSceneMgr* mgr;
public:
	LeftUi(CustomSceneMgr* mgr);
	~LeftUi();
	virtual void Release() override;
	SpriteObject* GetSprite() { return sprite; }
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	virtual void SetPos(Vector2f pos);
	virtual void SetEpisode(string str) { episodeId = str; }
	void Init() override;
};

