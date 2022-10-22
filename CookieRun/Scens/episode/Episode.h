#pragma once
#include "../Scene.h"

class SpriteObject;
class BackGround;
class VertexArrayObj;
class Cookie;
class Episode : public Scene
{
protected:
	string stageName;
	Texture* bottom;
	vector<BackGround*> back; // ��� ����
	vector<vector<IntRect>> rects;
	vector<VertexArrayObj*> bottoms;
	Cookie* cookie;

	float botmW;
	float botmH;
	
public:
	Episode();
	~Episode();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	void CreateBottom(Vector2f pos, vector<int> btmCnt, int rows);
};
