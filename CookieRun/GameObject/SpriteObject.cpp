#include "SpriteObject.h"

SpriteObject::SpriteObject()
{
}

SpriteObject::~SpriteObject()
{
	Release();
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
	if(enabled)
		window.draw(sprite);
	Object::Draw(window);
}

void SpriteObject::SetScale(Vector2f scale)
{
	sprite.setScale({ scale });
}
void SpriteObject::SetSize(Vector2f size)
{
	auto bound = sprite.getLocalBounds();
	sprite.setScale({ size.x / bound.width,size.y / bound.height });
}

void SpriteObject::SetPos(Vector2f pos)
{
	sprite.setPosition(pos);
	Object::SetPos(pos);
}

void SpriteObject::Translate(const Vector2f& delta)
{
	SetPos(position + delta);
}

void SpriteObject::SetTexture(Texture& tex)
{
	sprite.setTexture(tex,true);
}
void SpriteObject::SetColor(Color color)
{
	sprite.setColor(color);
}
Color SpriteObject::GetColor()
{
	return sprite.getColor();
}

void SpriteObject::SetOrigin(Origins origin)
{
	Utils::SetOrigin(sprite, origin);
}

FloatRect SpriteObject::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}