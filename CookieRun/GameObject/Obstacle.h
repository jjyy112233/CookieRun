#pragma once
#include "SpriteObject.h"

class Obstacle : public SpriteObject
{
private:
	Vector2f initPos;
public:
	Obstacle();
	virtual ~Obstacle();
	virtual void Init();
	virtual void SetPos(const Vector2f& pos);
	void SetInitPos(const Vector2f& pos);
	virtual void Translate(const Vector2f& delta);
	 void SetTexture(Texture& tex);
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};

