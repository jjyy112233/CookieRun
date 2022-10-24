#pragma once
#include "../Scene.h"

class SpriteObject;
class BackGround;
class VertexArrayObj;
class Cookie;
class Obstacle;

struct Stage
{
	string stageName;
	Texture* bottomTex;
	vector<BackGround*> backs; // 배경 정보
	vector<VertexArrayObj*> bottoms;
	vector<Obstacle*> obstacles;
	vector<int> bottomArray;
	bool isActive;

	void SetAcitve(bool active);
	bool GetActive()
	{
		return isActive;
	}
	bool isEnd();
	void Move();
	void SetBackGround(int i);
};

class Episode : public Scene
{
protected:
	int currStageIdx;
	Stage* currStage;
	string currStageName;
	string dataPath;

	vector<Stage*> stages;

	Cookie* cookie;

	float botmW;
	float botmH;
	
public:
	Episode(string dataPath);
	~Episode();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetStage(int idx);
	virtual void test();
	void CreateBottom(Vector2f pos, Stage* stage);
	void SetBackGround(Stage* prev, Stage* now);
};

