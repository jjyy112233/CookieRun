#pragma once
#include "../SpriteObject.h"
#include "../Animation/Animator.h"

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
		Count
	};
private:
	Animator animator;
	States currState;
	bool isJump;
	bool isDJump;
	const Vector2f* viewPos;
public:
	Cookie();
	void Init();
	void SetState(States newState);
	void Update(float dt);
	void UpdateInput(Event ev);
	void Draw(RenderWindow& window);
	void OnCompleteJump();
	void UpdateRun(float dt);
	void UpdateJump(float dt);
	void UpdateDoubleJump(float dt);
	void UpdateSlide(float dt);
	void UpdateDash(float dt);
	void UpdateDown(float dt);
	void UpdateFly(float dt);
};

