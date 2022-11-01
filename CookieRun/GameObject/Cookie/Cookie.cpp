#include "Cookie.h"
#include "../../Framework/ResourceManager.h"
#include "../../Framework/InputMgr.h"
#include "../../Framework/info.h"
#include "../../Scens/SceneManager.h"
#include "../../GameObject/VertexArrayObj.h"
#include "../../GameObject/Obstacle.h"
#include "../../GameObject/Jelly.h"
#include "../../Scens/episode/Episode.h"
#include "../../Ui/Episode/EpisodeUiMgr.h"


 Cookie::Cookie() : currState(States::None), viewPos(nullptr), timer(0.f),
	velocity(0.f,-1000.f), gravity(0.f,3000.f)
{

}

 void Cookie::SetEpi(Episode* epi)
 {
	 nowepisode = epi;
 }
void Cookie::Init()
{
	hp = 100.f;
	isInv = false;
	invTime = 0.f;
	animator.SetTarget(&sprite);
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Run"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Jump"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("DoubleJump"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Dash"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Fly"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Slide"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Down"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Bottom"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Fail"));
	animator.AddClip(*RESOURCES_MGR->GetAnimationClip("Clear"));

	SetState(States::Run);
	SetOrigin(Origins::TL);

	{
		auto down = *RESOURCES_MGR->GetAnimationClip("Bottom");
		AnimationEvent ev;
		ev.clipId = down.id;
		ev.frame = (int)down.frames.size()-1;
		ev.onEvent = bind(&Cookie::OnBottom, this);
		animator.AddEvent(ev);
	}

	auto cookieInfo = FILE_MGR->GetCookie("Jungle");

	for (auto& info : cookieInfo)
	{
		string type = info.first;
		vector<HitBox> hits;
		for (auto& hit : info.second.hitBox.circles)
		{
			HitBox h;
			h.shape = new CircleShape(hit.rad);
			h.initPos = hit.pos;
			h.SetPos(position);
			hits.push_back(h);
			Utils::SetOrigin(*h.shape, Origins::TL);
		}
		for (auto& hit : info.second.hitBox.rectangls)
		{
			HitBox h;
			h.shape = new RectangleShape(hit.size);
			h.initPos = hit.pos;
			h.SetPos(position);
			hits.push_back(h);
			Utils::SetOrigin(*h.shape, Origins::TL);
		}
		for (auto& hit : info.second.hitBox.points)
		{
			HitBox h;
			auto s = new ConvexShape(hit.points.size());
			int i = 0;
			for (auto p : hit.points)
				s->setPoint(i, p);

			h.shape = s;
			h.initPos = hit.pos;
			h.SetPos(position);
			hits.push_back(h);
			Utils::SetOrigin(*h.shape, Origins::TL);
		}

		HitBox bottom;
		bottom.shape = new RectangleShape{ info.second.bottom.size };
		bottom.initPos = info.second.bottom.pos;
		bottom.SetPos(position);
		hits.push_back(bottom);

		allBottom[type] = bottom;
		allHitBoxs[type] = hits;
	}

	hitBoxs = allHitBoxs["Run"];
	bottomHitBox = allBottom["Run"];

	//AddHitBox(RectangleShape({ 40,10 }), { 180,354 }, true);
	//AddHitBox(RectangleShape({ 45.f,52.f }), { 176,300 });
	//AddHitBox(CircleShape(38), { 186,234 });
}


void Cookie::SetBottom(vector<VertexArrayObj*>* botm)
{
	bottoms = botm;
	nowBottom = (*bottoms)[0];
}
void Cookie::NextBottom(vector<VertexArrayObj*>* botm)
{
	nextBottoms = botm;
}

void Cookie::SetObstacle(vector<Obstacle*>* obs)
{
	obstacles = obs;
}

void Cookie::SetJellys(vector<Jelly*>* jel)
{
	jellys = jel;
}

void Cookie::NextObstacle(vector<Obstacle*>* obs)
{
	nextObstacles = obs;
}

void Cookie::PrevJellys(vector<Jelly*>* jel)
{
	prevJellys = jel;
}

bool Cookie::ObstaclesHit()
{
	for (auto& obs : *obstacles)
	{
		auto obsHits = obs->GetHitBox();
		for (auto& obsHit : *obsHits)
		{
			for (auto& hit : hitBoxs)
				if (obsHit.shape->getGlobalBounds().intersects(hit.shape->getGlobalBounds()))
				{
					return true;
				}
		}
	}
	return false;
}

void Cookie::JellysHit()
{
	if (prevJellys != nullptr)
	{
		for (auto& jel : *prevJellys)
		{
			if (jel->GetActive())
			{
				auto jellyHits = jel->GetHitBox();
				for (auto& jellyHit : *jellyHits)
				{
					for (auto& hit : hitBoxs)
						if (jellyHit.shape->getGlobalBounds().intersects(hit.shape->getGlobalBounds()))
						{
							jel->SetActive(false);
							cout << "Hit Jelly" << endl;
							((Episode*)(SCENE_MGR->GetCurrScene()))->AddPoint(jel->getPoint());
						}
				}
			}
		}
	}
	for (auto& jel : *jellys)
	{
		if (jel->GetActive())
		{
			auto jellyHits = jel->GetHitBox();
			for (auto& jellyHit : *jellyHits)
			{
				for (auto& hit : hitBoxs)
					if (jellyHit.shape->getGlobalBounds().intersects(hit.shape->getGlobalBounds()))
					{
						jel->SetActive(false);
						cout << "Hit Jelly" << endl;
						((Episode*)(SCENE_MGR->GetCurrScene()))->AddPoint(jel->getPoint());
					}
			}
		}
	}
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
	if (nextBottoms != nullptr)
		for (auto& botm : *nextBottoms)
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
		hitBoxs = allHitBoxs["Run"];
		bottomHitBox = allBottom["Run"];
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
		hitBoxs = allHitBoxs["Slide"];
		bottomHitBox = allBottom["Slide"];
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
	case Cookie::States::Fail:
		isInv = false;
		invTime = 0.f;
		animator.Play("Fail");
		break;
	case Cookie::States::Clear:
		hitBoxs = allHitBoxs["Clear"];
		bottomHitBox = allBottom["Clear"];
		animator.Play("Clear");
		break;
	case Cookie::States::Count:
		break;
	default:
		break;
	}
	height = sprite.getGlobalBounds().height;
}

void Cookie::Update(float dt)
{
	if (viewPos == nullptr)
	{
		viewPos = &(SCENE_MGR->GetCurrScene())->GetWorldView().getCenter();
	}

	if (!nowepisode->GetIsEnd())
	{
		UpdateInput();
		JellysHit();
		if (currState != States::Fail)
		{
			if (ObstaclesHit() && !invTime)
			{
				((EpisodeUiMgr*)(SCENE_MGR->GetCurrScene()->GetUiMgr()))->SetHp();
				cout << "Hit Obs" << endl;
				hp -= 10;
				isInv = true;
				SetColor(Color::White);
				invTime = 0.f;
				invColorTime = 0.f;
			}

			if (isInv)
			{
				invColorTime += dt;
				invTime += dt;

				if (invColorTime > 0.1f)
				{
					invColorTime = 0.f;
					auto color = GetColor();
					SetColor(color.a != 255 ? Color::White : Color(255, 255, 255, 100));
				}
			}

			if (invTime > 1.f)
			{
				invTime = 0.f;
				invColorTime = 0.f;
				SetColor(Color::White);
				isInv = false;
			}
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
		case Cookie::States::Fail:
			UpdateFail(dt);
			break;
		case Cookie::States::Clear:
			UpdateFallDie(dt);
		case Cookie::States::FallDie:
			UpdateFallDie(dt);
			break;
		case Cookie::States::Count:
			break;
		default:
			break;
		}
	}
	else
	{
		Translate(Vector2f{ 0,1 } *500.f * dt);
		if (IsBottomHit())
		{
			SetState(States::Clear);
			SetPos({ position.x, nowBottom->GetGlobalBounds().top - height });
		}
		Translate(Vector2f{ 1,0 } *500.f * dt);
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
		else if(currState == States::Run || currState == States::Bottom)
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
	//SetPos(InputMgr::GetMousePos() - Vector2f{GetGlobalBound().width /2, GetGlobalBound().height/2});
	SetPos({ viewPos->x - 400.f, position.y + dt * 500.f });
	if (IsBottomHit())
	{
		SetPos({ viewPos->x - 400.f, nowBottom->GetGlobalBounds().top - height});
	}
	else
	{
		if (nowBottom->GetGlobalBounds().top > position.y + height)
		{
		}
		else
		{
			SetState(States::Down);
		}
	}
}

void Cookie::UpdateJump(float dt)
{
	velocity += gravity * dt;
	Vector2f delta = velocity * dt;
	Translate(delta);
	SetPos({ viewPos->x - 400.f,position.y });


	if (nowBottom->GetGlobalBounds().top < position.y + height)
	{
		//SetState(States::Down);
	}
	if (IsBottomHit())
	{
		SetPos({ viewPos->x - 400.f, nowBottom->GetGlobalBounds().top - height });
		SetState(States::Bottom);
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
	if (nowBottom->GetGlobalBounds().top < position.y + height)
	{
		//SetState(States::Down);
	}
	if (IsBottomHit())
	{
		SetState(States::Bottom);
		velocity = Vector2f(0.f, -1000.f);
		gravity = Vector2f(0.f, 3000.f);
		SetPos({ viewPos->x - 400.f, nowBottom->GetGlobalBounds().top - height });
	}
	if (IsBottomBodyHit())
	{
		SetState(States::FallDie);
		return;
	}
}

void Cookie::UpdateSlide(float dt)
{
	SetPos({ viewPos->x - 400.f, position.y + dt * 500.f });
	if (IsBottomHit())
	{
		SetPos({ viewPos->x - 400.f, nowBottom->GetGlobalBounds().top - height });
	}
	else
	{
		if (nowBottom->GetGlobalBounds().top > position.y + height)
		{
		}
		else
		{
			SetState(States::Down);
		}
	}

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
	SetPos({ viewPos->x - 400.f, nowBottom->GetGlobalBounds().top - height });
}

void Cookie::UpdateFly(float dt)
{
}

void Cookie::UpdateFallDie(float dt)
{
	SetPos({ viewPos->x - 400.f,position.y + dt * 1000.f });
	((Episode*)SCENE_MGR->GetCurrScene())->SetIsFail(true);
}
void Cookie::UpdateFail(float dt)
{
	SetPos({ viewPos->x - 400.f, position.y + dt * 500.f });
	if (IsBottomHit())
	{
		SetPos({ viewPos->x - 400.f, nowBottom->GetGlobalBounds().top - height });
	}

	((Episode*)SCENE_MGR->GetCurrScene())->SetIsFail(true);
}

void Cookie::Fail()
{
	SetState(States::Fail);
}
