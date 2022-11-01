#include "EpisodeUiMgr.h"
#include "../../GameObject/SpriteObject.h"
#include "../../GameObject/TextObject.h"
#include "../../Framework/ResourceManager.h"
#include "../../Framework/Utils.h"
#include "../../Framework/info.h"
#include "../../Scens/episode/Episode.h";
#include "../../Scens/SceneManager.h"
#include "../../Ui/Episode/GameEnd.h"

EpisodeUiMgr::EpisodeUiMgr(Scene* scene)
	:UiMgr(scene)
{
}

EpisodeUiMgr::~EpisodeUiMgr()
{
	Release();
}

void EpisodeUiMgr::Init()
{
	UiMgr::Init();
	stop = false;
	stageBar = new SpriteObject();
	miniCookie = new SpriteObject();
	hpBar = new SpriteObject();
	point = new TextObject();

	gameEnd = new GameEnd();
	gameEnd->Init();
	gameEnd->SetActive(false);
	uiObjList[0].push_back(gameEnd);

	point->SetText(*RESOURCES_MGR->GetFont("fonts/CookieRun Bold.ttf"), 50, Color::White, "000");
	hpBar->SetTexture(*RESOURCES_MGR->GetTexture("graphics/hpBar.png"));
	miniCookie->SetTexture(*RESOURCES_MGR->GetTexture("graphics/miniCookie.png"));
	stageBar->SetTexture(*RESOURCES_MGR->GetTexture("graphics/stageBar.png"));

	hpBar->SetPos({ 20,20 });
	hpSzie = hpBar->GetGlobalBound().width;
	stageBar->SetPos({ 75,75 });
	miniCookie->SetPos({ 75,75 });
	point->SetOrigin(Origins::TR);
	point->SetPosition({ WINDOW_WIDTH - 50,20 });

	nonTouchObj.push_back(stageBar);
	nonTouchObj.push_back(miniCookie);
	nonTouchObj.push_back(hpBar);
	nonTouchObj.push_back(point);
}

void EpisodeUiMgr::Update(float dt)
{
	if (!stop)
	{
		miniCookie->Translate({ dt * miniCkSpeed ,0 });

		hpSzie -= (dt * 10);

		if (hpSzie < 60.f)
		{
			stop = true;
			((Episode*)parentScene)->CookieIsFail();
			((Episode*)parentScene)->SetTimeOut(true);
		}
		hpBar->GetSprite().setTextureRect(IntRect{ 0,0,(int)hpSzie, 60 });
	}

	for (auto& obj : nonTouchObj)
	{
		obj->Update(dt);
	}
	UiMgr::Update(dt);
}

void EpisodeUiMgr::Draw(RenderWindow& window)
{
	for (auto& obj : nonTouchObj)
	{
		obj->Draw(window);
	}

	UiMgr::Draw(window);
}

string sep_thousands(int f) 
{ 
	using namespace std;
	const char* locale_name = "korean";
	ostringstream oss;
	oss.imbue(locale(locale_name));
	oss << f;
	return oss.str(); 
}
void EpisodeUiMgr::SetPoint(int point)
{
	string nowPoinStr = sep_thousands(point);
	this->point->SetString(nowPoinStr);
	this->point->SetOrigin(Origins::TR);
	this->point->SetPosition({ WINDOW_WIDTH - 50,20 });
}

void EpisodeUiMgr::SetHp()
{
	hpSzie += - 20;
	hpBar->GetSprite().setTextureRect(IntRect{ 0,0,(int)hpSzie, 60 });
 }

void EpisodeUiMgr::setSpeed(float size)
{
	miniCookie->SetPos({ 75,75 });
	stageSize = size;
	miniCkSpeed = parentScene->GetViewSpeed() * ((stageBar->GetGlobalBound().width-20) / stageSize);
}

void EpisodeUiMgr::setStop()
{
	stop = true;
}

void EpisodeUiMgr::SetEnd()
{
	gameEnd->SetActive(true);
	gameEnd->SetPoint(point->GetString());
}
