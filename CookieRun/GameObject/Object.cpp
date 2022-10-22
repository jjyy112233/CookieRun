#include "Object.h"
#include "../Framework/Utils.h"
#define DEBUG

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
	enabled = true;
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
	hit.shape->setFillColor(Color::Red);
	hit.initPos = pos;
	hit.SetPos(position);

	hitBoxs.push_back(hit);

	if (isBottom)
		bottomHitBox = hit;
	Utils::SetOrigin(*hit.shape, Origins::BC);
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
void Object::AddHitBox(ConvexShape hitbox, vector<Vector2f> points, Vector2f pos, bool isBottom)
{

	HitBox hit = HitBox();

	hitbox.setPointCount(points.size());
	int idx = 0;
	for (auto& point : points)
	{
		hitbox.setPoint(idx, point);
		idx++;
	}

	hit.shape = new ConvexShape(hitbox);

	hit.SetPos(position);

	Utils::SetOrigin(*hit.shape, Origins::BC);


	hit.shape->setFillColor(Color(255,0,0,120));
	hit.initPos = pos;

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
