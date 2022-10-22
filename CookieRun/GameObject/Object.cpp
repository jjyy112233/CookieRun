#include "Object.h"
#include "../Framework/Utils.h"
#define DEBUG

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
	for (auto& hitbox : hitBoxs)
	{
		if (hitbox.shape != nullptr)
			delete hitbox.shape;
	}
	hitBoxs.clear();
}

void Object::SetPos(const Vector2f& pos)
{
	position = pos;
	for (auto& hit : hitBoxs)
	{
		hit.SetPos(position);
	}
}
void Object::Translate(const Vector2f& delta)
{
	SetPos(position + delta);
}

const Vector2f& Object::GetPos() const
{
	return position;
}

void Object::AddHitBox(RectangleShape hitbox, Vector2f pos, bool isBottom)
{
	HitBox hit = HitBox();
	hit.initPos = pos;
	hit.shape = new RectangleShape(hitbox);
	Utils::SetOrigin(*hit.shape, Origins::BC);
	hit.shape->setFillColor(Color::Red);
	hit.initPos = pos;
	hit.SetPos(position);

	hitBoxs.push_back(hit);

	if (isBottom)
		bottomHitBox = hit;
}
void Object::AddHitBox(CircleShape hitbox, Vector2f pos, bool isBottom)
{
	HitBox hit = HitBox();
	hit.initPos = pos;
	hit.shape = new CircleShape(hitbox);
	Utils::SetOrigin(*hit.shape, Origins::BC);
	hit.shape->setFillColor(Color::Red);
	hit.initPos = pos;
	hit.SetPos(position);

	hitBoxs.push_back(hit);
	if (isBottom)
		bottomHitBox = hit;
}

const vector<HitBox>* Object::GetHitBox()
{
	return &hitBoxs;
}

const HitBox& Object::GetHitBoxBottom()
{
	return bottomHitBox;
}

void Object::Update(float dt)
{
}

void Object::Draw(RenderWindow& window)
{
	for (auto& hitbox : hitBoxs)
	{
		window.draw(*hitbox.shape);
	}
}
