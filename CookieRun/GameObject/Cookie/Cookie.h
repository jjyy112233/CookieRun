#pragma once
#include "../SpriteObject.h"
#include "../Animation/Animator.h"

class VertexArrayObj;
class Obstacle;
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
	Vector2f velocity;
	Vector2f gravity;
	vector<VertexArrayObj*>* bottoms;
	vector<VertexArrayObj*>* nextBottoms;
	vector<Obstacle*>* obstacles;
	vector<Obstacle*>* nextObstacles;
	VertexArrayObj* nowBottom;

	float height;
public:
	Cookie();
	virtual void Init();
	void SetBottom(vector<VertexArrayObj*>* botm);
	void NextBottom(vector<VertexArrayObj*>* botm);
	void SetObstacle(vector<Obstacle*>* obs);
	void NextObstacle(vector<Obstacle*>* obs);
	bool ObstaclesHit();
	bool IsBottomHit();
	bool IsBottomBodyHit();
	void SetState(States newState);
	virtual void Update(float dt);
	void UpdateInput();
	virtual void Draw(RenderWindow& window);
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

