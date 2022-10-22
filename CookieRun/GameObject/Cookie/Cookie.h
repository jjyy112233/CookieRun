#pragma once
#include "../SpriteObject.h"
#include "../Animation/Animator.h"

class VertexArrayObj;
class Cookie : public SpriteObject
{
public:
	enum class States
	{
		None = -1,
		Run,
		Jump,
		DoubleJump,
		Slide,
		Dash,
		Fly,
		Down,
		Bottom,
		FallDie,
		Count
	};
private:
	Animator animator;
	States currState;
	const Vector2f* viewPos;

	float timer;
	float jumpTime;
	Vector2f velocity;
	Vector2f gravity;
	vector<VertexArrayObj*>* bottoms;
	VertexArrayObj* nowBottom;
public:
	Cookie();
	void Init();
	void SetBottom(vector<VertexArrayObj*>* botm);
	bool IsBottomHit();
	bool IsBottomBodyHit();
	void SetState(States newState);
	void Update(float dt);
	void UpdateInput();
	void Draw(RenderWindow& window);
	void OnBottom();
	void UpdateRun(float dt);
	void UpdateJump(float dt);
	void UpdateDoubleJump(float dt);
	void UpdateSlide(float dt);
	void UpdateDash(float dt);
	void UpdateDown(float dt);
	void UpdateBottom(float dt);
	void UpdateFly(float dt);
	void UpdateFallDie(float dt);
};

