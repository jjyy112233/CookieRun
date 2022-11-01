#pragma once
#include "../UiMgr.h"

class SpriteObject;
class TextObject;
class Scene;
class Episode;
class GameEnd;
class EpisodeUiMgr : public UiMgr
{
private:
	SpriteObject* stageBar;
	SpriteObject* miniCookie;
	SpriteObject* hpBar;
	TextObject* point;
	Episode* epi;

	GameEnd* gameEnd;
	vector<Object*> nonTouchObj;
	float miniCkSpeed;
	float stageSize;
	float hpSzie;

	bool stop;

public:
	EpisodeUiMgr(Scene* scene);
	virtual ~EpisodeUiMgr();
	void Init();
	void Update(float dt);
	void Draw(RenderWindow& window);
	void SetPoint(int point);
	void SetHp();
	void setSpeed(float size);
	void setStop();
	void SetEnd();
};

