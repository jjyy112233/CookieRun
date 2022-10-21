#include "SpriteObject.h"

SpriteObject::SpriteObject()
{
}

SpriteObject::~SpriteObject()
{
}

void SpriteObject::Init()
{
}

void SpriteObject::Update(float dt)
{
	Object::Update(dt);
}

void SpriteObject::Draw(RenderWindow& window)
{
	window.draw(sprite);
	Object::Draw(window);
}

void SpriteObject::SetScale(Vector2f scale)
{
	sprite.setScale(scale);
}

void SpriteObject::SetPos(Vector2f pos)
{
	Object::SetPos(pos);
	sprite.setPosition(pos);
}

void SpriteObject::Translate(const Vector2f& delta)
{
	SetPos(position + delta);
}

void SpriteObject::SetTexture(Texture& tex)
{
	sprite.setTexture(tex,true);
	sprite.setScale(initScale);
}

void SpriteObject::SetOrigin(Origins origin)
{
	Utils::SetOrigin(sprite, origin);
}