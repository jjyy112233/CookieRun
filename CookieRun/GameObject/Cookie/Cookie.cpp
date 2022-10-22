#include "Cookie.h"
#include "../../Framework/ResourceManager.h"
#include "../../Framework/InputMgr.h"
#include "../../Framework/info.h"
#include "../../Scens/SceneManager.h"
#include "../../GameObject/VertexArrayObj.h"


 Cookie::Cookie() : currState(States::None), viewPos(nullptr), timer(0.f), jumpTime(0.5f),
	velocity(0.f,-1000.f), gravity(0.f,3000.f)
{

}
void Cookie::Init()
{
	animator.SetTarget(&sprite);
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Run"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Jump"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("DoubleJump"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Dash"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Fly"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Slide"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Down"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Bottom"));
	SetState(States::Run);
	SetOrigin(Origins::BC);
	jumpTime = 0.f;


	{
		auto down = *RESOURCES_MGR->GetAnimationClip("Bottom");
		AnimationEvent ev;
		ev.clipId = down.id;
		ev.frame = (int)down.frames.size()-1;
		ev.onEvent = bind(&Cookie::OnBottom, this);
		animator.AddEvent(ev);
	}

	AddHitBox(RectangleShape({ 40.f,28.f }), { 0,0 }, true);
	AddHitBox(RectangleShape({ 45.f,52.f }), { 22,-16 });
	AddHitBox(CircleShape(38), { 40,-52 });
}


void Cookie::SetBottom(vector<VertexArrayObj*>* botm)
{
	bottoms = botm;
	nowBottom = (*bottoms)[0];
}

bool Cookie::IsBottomHit()
{
	for (auto& botm : *bottoms)
	{
		if (botm->GetGlobalBounds().intersects(bottomHitBox.shape->getGlobalBounds()))
			//if(botm->GetGlobalBounds().intersects(SpriteObject::GetGlobalBound()))
		{
			nowBottom = botm;
			return true;
		}
	}
	return false;
}

bool Cookie::IsBottomBodyHit()
{
	for (auto& botm : *bottoms)
	{
		for (auto& hit : hitBoxs)
		{
			if (hit.shape == bottomHitBox.shape)
				continue;
			if (botm->GetGlobalBounds().intersects(hit.shape->getGlobalBounds()))
			{
				nowBottom = botm;
				return true;
			}
		}
	}
	return false;
}

void Cookie::SetState(States newState)
{
	if (currState == newState)
		return;

	currState = newState;
	switch (currState)
	{
	case Cookie::States::None:
		break;
	case Cookie::States::Run:
		animator.Play("Run");
		break;
	case Cookie::States::Jump:
		animator.Play("Jump");
		break;
	case Cookie::States::DoubleJump:
		velocity = Vector2f(0.f, -1000.f);
		gravity = Vector2f(0.f, 3000.f);
		animator.Play("DoubleJump");
		break;
	case Cookie::States::Slide:
		animator.Play("Slide");
		break;
	case Cookie::States::Dash:
		break;
	case Cookie::States::Fly:
		break;
	case Cookie::States::Down:
		animator.Play("Down");
		break;
	case Cookie::States::Bottom:
		animator.Play("Bottom");
		break;
	case Cookie::States::FallDie:
		break;
	case Cookie::States::Count:
		break;
	default:
		break;
	}

}

void Cookie::Update(float dt)
{
	UpdateInput();

	if (viewPos == nullptr)
	{
		viewPos = &(SCENE_MGR->GetCurrScene())->GetWorldView().getCenter();

	}

	switch (currState)
	{
	case Cookie::States::None:
		break;
	case Cookie::States::Run:
		UpdateRun(dt);
		break;
	case Cookie::States::Jump:
		UpdateJump(dt);
		break;
	case Cookie::States::DoubleJump:
		UpdateDoubleJump(dt);
		break;
	case Cookie::States::Slide:
		UpdateSlide(dt);
		break;
	case Cookie::States::Dash:
		break;
	case Cookie::States::Fly:
		break;
	case Cookie::States::Down:
		UpdateDown(dt);
		break;
	case Cookie::States::Bottom:
		UpdateBottom(dt);
		break;
	case Cookie::States::FallDie:
		UpdateFallDie(dt);
		break;
	case Cookie::States::Count:
		break;
	default:
		break;
	}

	animator.Update(dt);
	SpriteObject::Update(dt);
}

void Cookie::UpdateInput()
{
	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		if (currState == States::Jump || currState == States::Down)
		{
			SetState(States::DoubleJump);
		}
		else if(currState == States::Run)
		{
			SetState(States::Jump);

		}
	}

	if ((currState == States::Run || currState == States::Bottom)&& InputMgr::GetKeyDown(Keyboard::Down))
	{
		SetState(States::Slide);
	}
	if (InputMgr::GetKeyUp(Keyboard::Down))
	{
		if(currState == States::Slide)
			SetState(States::Run);
	}
}

void Cookie::Draw(RenderWindow& window)
{
	window.draw(sprite);
	SpriteObject::Draw(window);
}

void Cookie::OnBottom()
{
	SetState(States::Run);
}

void Cookie::UpdateRun(float dt)
{
	SetPos({ viewPos->x - 400.f,position.y + dt * 500.f });
	if (IsBottomHit())
	{
		SetPos({ viewPos->x - 400.f, nowBottom->GetGlobalBounds().top});
	}
	else
	{
		std::cout << nowBottom->GetGlobalBounds().top << std::endl;
		if (nowBottom->GetGlobalBounds().top > position.y)
		{
			std::cout << "Down" << std::endl;
		}
		else
		{
			SetState(States::Down);
			std::cout << "Fall" << std::endl;
		}
	}
}

void Cookie::UpdateJump(float dt)
{
	velocity += gravity * dt;
	Vector2f delta = velocity * dt;
	Translate(delta);
	SetPos({ viewPos->x - 400.f,position.y });

	if (IsBottomHit())
	{
		SetState(States::Bottom);
		SetPos({ viewPos->x - 400.f,  position.y });
		velocity = Vector2f(0.f, -1000.f);
		gravity = Vector2f(0.f, 3000.f);
	}

}

void Cookie::UpdateDoubleJump(float dt)
{
	velocity += gravity * dt;
	Vector2f delta = velocity * dt;
	Translate(delta);
	SetPos({ viewPos->x - 400.f,position.y });

	if (velocity.y > 500)
	{
		animator.Play("Down");
	}
	if (IsBottomHit())
	{
		SetState(States::Bottom);
		velocity = Vector2f(0.f, -1000.f);
		gravity = Vector2f(0.f, 3000.f);
		SetPos({ viewPos->x - 400.f, nowBottom->GetGlobalBounds().top });
	}
	//std::cout << position.y << std::endl;
}

void Cookie::UpdateSlide(float dt)
{
	SetPos({ viewPos->x - 400.f, nowBottom->GetGlobalBounds().top });
}

void Cookie::UpdateDash(float dt)
{
}

void Cookie::UpdateDown(float dt)
{
	SetPos({ viewPos->x - 400.f,position.y + dt * 500.f });
	if (IsBottomBodyHit())
	{
		SetState(States::FallDie);
	}
}

void Cookie::UpdateBottom(float dt)
{
	SetPos({ viewPos->x - 400.f, nowBottom->GetGlobalBounds().top });
}

void Cookie::UpdateFly(float dt)
{
}

void Cookie::UpdateFallDie(float dt)
{
	SetPos({ viewPos->x - 400.f,position.y + dt * 1000.f });
	SCENE_MGR->GetCurrScene()->SetViewStop();
}