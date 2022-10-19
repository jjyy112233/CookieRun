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

void SpriteObject::SetTexture(Texture& tex)
{
	sprite.setTexture(tex);
}
