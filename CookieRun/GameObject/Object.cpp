#include "Object.h"

Object::Object()
{
	Init();
	Init();
}

Object::~Object()
{
	Release();
}

bool Object::GetActive() const
{
	return enabled;
}

void Object::SetActive(bool active)
{
	enabled = active;
}

void Object::Init()
{
	initScale = { 2.f, 2.f };
}

void Object::Release()
{
}

void Object::SetPos(const Vector2f& pos)
{
	position = pos;
}
void Object::Translate(const Vector2f& delta)
{
	SetPos(position + delta);
}

void Object::SetPos(float x, float y)
{
	position = { x,y };
}

const Vector2f& Object::GetPos() const
{
	return position;
}

void Object::Update(float dt)
{
}

void Object::Draw(RenderWindow& window)
{
}
