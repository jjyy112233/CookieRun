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
}

void Obstacle::SetPos(const Vector2f& pos)
{
	Vector2f delta = pos - position;
	SpriteObject::SetPos(position + delta);
}


void Obstacle::Translate(const Vector2f& delta)
{
	SpriteObject::Translate(delta);
}

void Obstacle::SetTexture(Texture& tex)
{
	sprite.setTexture(tex);
	SetOrigin(Origins::BC);
}

void Obstacle::Update(float dt)
{
}

void Obstacle::Draw(RenderWindow& window)
{
	SpriteObject::Draw(window);
}
