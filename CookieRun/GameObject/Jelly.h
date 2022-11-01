#pragma once
#include "../GameObject/SpriteObject.h"
#include "Animation/Animator.h"

class Jelly : public SpriteObject
{
private:
	int point;
	Vector2f initPos;

	Animator animator;
	bool isAnime;
public:
	Jelly();
	virtual ~Jelly();
	void SetAnime(bool state) { isAnime = state; }
	virtual void Init();
	virtual void SetPos(const Vector2f& pos);
	void SetInitPos(const Vector2f& pos);
	virtual void Translate(const Vector2f& delta);
	void SetTexture(Texture& tex);
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	void HitPlayer();
	int getPoint() { return point; }
};

