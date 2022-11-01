#include "Jelly.h"
#include "../../Framework/ResourceManager.h"

Jelly::Jelly()
	:isAnime(true)
{
	
}

Jelly::~Jelly()
{
	Release();
}

void Jelly::Init()
{
	SpriteObject::Init();
	AddHitBox(FILE_MGR->GetHitBox(GetName()), initPos);
	point = RESOURCES_MGR->GetPoints(GetName());

	if (isAnime)
	{
		animator.SetTarget(&sprite);
		animator.AddClip(*RESOURCES_MGR->GetAnimationClip(GetName()));
		animator.Play(GetName());
	}
}

void Jelly::SetPos(const Vector2f& pos)
{
	Vector2f delta = pos - position;
	SpriteObject::SetPos(position + delta);
}
void Jelly::SetInitPos(const Vector2f& pos)
{
	initPos = pos;
}

void Jelly::Translate(const Vector2f& delta)
{
	SpriteObject::Translate(delta);
}

void Jelly::SetTexture(Texture& tex)
{
	sprite.setTexture(tex);
}

void Jelly::Update(float dt)
{
	animator.Update(dt);
	SpriteObject::Update(dt);
}

void Jelly::Draw(RenderWindow& window)
{
	SpriteObject::Draw(window);
}

void Jelly::HitPlayer()
{

}
