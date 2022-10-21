#pragma once
#include "../../GameObject/SpriteObject.h"

using namespace sf;
using namespace std;

class BackGround : public SpriteObject
{
private:
	SpriteObject right;
	SpriteObject right2;
	int width;
	int height;
	float speed;
	
public:
	BackGround(Texture* tex, float spd);
	void Update(float dt);
	void Draw(RenderWindow& window);
};

