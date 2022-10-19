#include "Object.h"

Object::Object()
{
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
}

void Object::Release()
{
}

void Object::SetPos(const Vector2f& pos)
{
	position = pos;
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
