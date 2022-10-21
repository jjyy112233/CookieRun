#include "Cookie.h"
#include "../../Framework/ResourceManager.h"
#include "../../Framework/InputMgr.h"
#include "../../Framework/info.h"
#include "../../Scens/SceneManager.h"


 Cookie::Cookie() : currState(States::None), viewPos(nullptr)
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
	SetState(States::Run);
	SetOrigin(Origins::BC);
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
		break;
	case Cookie::States::DoubleJump:
		break;
	case Cookie::States::Slide:
		break;
	case Cookie::States::Dash:
		break;
	case Cookie::States::Fly:
		break;
	case Cookie::States::Down:
		break;
	case Cookie::States::Count:
		break;
	default:
		break;
	}

}

void Cookie::Update(float dt)
{
	if (viewPos == nullptr)
		viewPos = &(SCENE_MGR->GetCurrScene())->GetWorldView().getCenter();

	switch (currState)
	{
	case Cookie::States::None:
		break;
	case Cookie::States::Run:
		UpdateRun(dt);
		break;
	case Cookie::States::Jump:
		break;
	case Cookie::States::DoubleJump:
		break;
	case Cookie::States::Slide:
		break;
	case Cookie::States::Dash:
		break;
	case Cookie::States::Fly:
		break;
	case Cookie::States::Down:
		break;
	case Cookie::States::Count:
		break;
	default:
		break;
	}

	SetPos(*viewPos + Vector2f{-400.f, 220.f});

	animator.Update(dt);
	SpriteObject::Update(dt);
}

void Cookie::UpdateInput(Event ev)
{
}

void Cookie::Draw(RenderWindow& window)
{
	window.draw(sprite);
	SpriteObject::Draw(window);
}

void Cookie::OnCompleteJump()
{
}

void Cookie::UpdateRun(float dt)
{
}

void Cookie::UpdateJump(float dt)
{
}

void Cookie::UpdateDoubleJump(float dt)
{
}

void Cookie::UpdateSlide(float dt)
{
}

void Cookie::UpdateDash(float dt)
{
}

void Cookie::UpdateDown(float dt)
{
}

void Cookie::UpdateFly(float dt)
{
}
