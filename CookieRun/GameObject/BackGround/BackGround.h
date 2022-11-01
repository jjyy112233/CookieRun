#pragma once
#include "../../GameObject/SpriteObject.h"

using namespace sf;
using namespace std;

class BackGround : public SpriteObject
{
public:
	enum class BackState
	{
		None,
		Disable,
		Enable,
	};
private:
	SpriteObject right;
	SpriteObject right2;
	int width;
	int height;
	float speed;

	float color;
	BackState state;
	float timer;
	bool isStop;
	
public:
	BackGround(Texture* tex, float spd);
	void Update(float dt);
	void SetBackgroundState(BackGround::BackState s);
	void UpdateBackGround(float dt);
	void SetActive(bool active);
	void Draw(RenderWindow& window);
	void SetStop(bool state) { isStop = state; }
};

