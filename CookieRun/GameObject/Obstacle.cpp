#include "Obstacle.h"

Obstacle::Obstacle()
{
}

Obstacle::~Obstacle()
{
}

void Obstacle::Init()
{
	SpriteObject::Init();
	AddHitBox(FILE_MGR->GetHitBox(GetName()), initPos);
}

void Obstacle::SetPos(const Vector2f& pos)
{
	Vector2f delta = pos - position;
	SpriteObject::SetPos(position + delta);
}
void Obstacle::SetInitPos(const Vector2f& pos)
{
	initPos = pos;
}
void Obstacle::Translate(const Vector2f& delta)
{
	SpriteObject::Translate(delta);
}

void Obstacle::SetTexture(Texture& tex)
{
	sprite.setTexture(tex);
}

void Obstacle::Update(float dt)
{
	SpriteObject::Update(dt);
}

void Obstacle::Draw(RenderWindow& window)
{
	SpriteObject::Draw(window);
}
