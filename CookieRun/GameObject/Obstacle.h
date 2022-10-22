#pragma once
#include "SpriteObject.h"

class Obstacle : public SpriteObject
{
public:
	Obstacle();
	virtual ~Obstacle();
	virtual void Init();
	virtual void SetPos(const Vector2f& pos);
	virtual void Translate(const Vector2f& delta);
	 void SetTexture(Texture& tex);
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};

