#include "Episode.h"
#include "../SceneManager.h"
#include "../../Framework/InputMgr.h"
#include "../../Framework/ResourceManager.h"
#include "../../GameObject/BackGround/BackGround.h"
#include "../../GameObject/TextObject.h"
#include "../../Framework/SoundManager.h"
#include "../../Framework/info.h"
#include "../../GameObject/VertexArrayObj.h"
#include "../../GameObject/Cookie/Cookie.h"
#include "../../GameObject/Obstacle.h"
#include "../../Framework/FileManager.h"
#include "../../Ui/Custom/CustomSceneMgr.h"
#include "../../GameObject/Jelly.h"
#include "../../Ui/Episode/EpisodeUiMgr.h"

Episode::Episode(string dataPath)
	:Scene(Scenes::Episode), isEnding(false)
{
    botmW = 124.f;
    botmH = 200.f;
}

Episode::~Episode()
{
	Release();
}

void Episode::Init()
{
	point = 0;
	currStageIdx = 0;
	isEnding = false;
	isFail = false;
	isTimeOut = false;
	failTimer = 0.f;
	auto episodeData = FILE_MGR->GetEpisode(currEpisodeName);
	for (auto& pair : episodeData)
	{
		auto stageInfo = pair.second;

		Stage* stage = new Stage();
		stages.push_back(stage);

		vector<ns::BackInfo>  backInfo = stageInfo.backInfo;

		for (auto& info : backInfo)
		{
			BackGround* back = new BackGround(RESOURCES_MGR->GetTexture(info.path), info.speed);
			stage->backs.push_back(back);
		}
		stage->bottomTex = RESOURCES_MGR->GetTexture(stageInfo.bottomPath);
		stage->bottomArray = stageInfo.bottomPos;
		CreateBottom({ 0.f,0.f }, stage);
		stage->SetBackGround((int)BackGround::BackState::Enable);


		map<string, vector<sf::Vector2f>> obstacles = stageInfo.obstacles;
		
		for (auto& obsInfo : obstacles)
		{
			string path = obsInfo.first;

			for (auto& obsPos : obsInfo.second)
			{
				Obstacle* obs = new Obstacle;
				obs->SetTexture(*RESOURCES_MGR->GetTexture(path));
				obs->SetName(path);
				obs->SetPos(obsPos);
				obs->SetInitPos(obsPos);
				obs->Init();

				objList[LayerType::Object][0].push_back(obs);
				stage->obstacles.push_back(obs);
				stage->SetAcitve(false);
			}
		}
		{
			map<string, vector<sf::Vector2f>> jellys = stageInfo.jellys;
			for (auto& jellyInfo : jellys)
			{
				string path = jellyInfo.first;

				for (auto& jelPos : jellyInfo.second)
				{
					Jelly* jelly = new Jelly;
					jelly->SetTexture(*RESOURCES_MGR->GetTexture(path));
					jelly->SetName(path);
					jelly->SetPos(jelPos);
					jelly->SetInitPos(jelPos);
					jelly->Init();

					objList[LayerType::Object][0].push_back(jelly);
					stage->jelly.push_back(jelly);
					stage->SetAcitve(false);
				}
			}
		}
	}

	uiMgr = new EpisodeUiMgr(this);
	uiMgr->Init();

	{
		SetStage(0); 
	}


	cookie = new Cookie();
	objList[LayerType::Cookie][0].push_back(cookie);
	cookie->SetEpi(this);
	cookie->SetBottom(&currStage->bottoms);
	cookie->SetObstacle(&currStage->obstacles);
	cookie->SetJellys(&currStage->jelly);
	cookie->Init();

	//uiMgr = new CustomSceneMgr(this);
}

void Episode::Release()
{
	Scene::Release();
}

void Episode::Enter()
{
	SCENE_MGR->GetCurrScene()->SetViewPlay();
	worldView.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	worldView.setCenter({ WINDOW_WIDTH/2,WINDOW_HEIGHT/2});
	Init();
}

void Episode::Exit()
{
	Release();
	stages.clear();
}
void Episode::Reset()
{
	point = 0;
	currStageIdx = 0;
	isEnding = false;
	isFail = false;
	isTimeOut = false;
	failTimer = 0.f;

	for (auto& layer : objList)
	{
		for (auto& obj_pair : layer.second)
		{
			auto objs = obj_pair.second;
			for (auto& obj : objs)
			{
				obj->Release();
				obj->Init();
			}
		}
	}

	uiMgr->Init();
	{
		SetStage(0);
	}

	cookie->SetBottom(&currStage->bottoms);
	cookie->SetObstacle(&currStage->obstacles);
	cookie->SetJellys(&currStage->jelly);
	cookie->Init();

	//uiMgr = new CustomSceneMgr(this);
}

void Episode::Update(float dt)
{
	Scene::Update(dt);

	if (isTimeOut || isFail || isEnding)
	{
		for (auto& back : currStage->backs)
		{
			back->SetStop(true);
		}
		failTimer += dt;
		if (failTimer > 2.f)
		{
			((EpisodeUiMgr*)uiMgr)->SetEnd();
		}
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		//SCENE_MGR->ChangeScene(Scenes::Episode2);
		return;
	}

	if (currStage->isEnd())
	{
		currStageIdx++;

		if (isEnding)
			return;
		if (stages.size() <= currStageIdx)
		{
			isEnding = true;
			SCENE_MGR->GetCurrScene()->SetViewStop();
			((EpisodeUiMgr*)uiMgr)->setStop();
			return;
		}


		auto prev = currStage;
		SetStage(currStageIdx);
		cookie->SetBottom(&currStage->bottoms);
		cookie->NextBottom(&prev->bottoms);
		SetBackGround(prev, currStage);

		cookie->SetObstacle(&currStage->obstacles);
		cookie->SetJellys(&currStage->jelly);
		cookie->PrevJellys(&prev->jelly);
		cookie->NextObstacle(&prev->obstacles);

		currStage->Move();
	}
	if (InputMgr::GetKeyDown(Keyboard::Tab))
	{
		SCENE_MGR->ChangeScene(Scenes::EpisodeList);
		return;
	}

}

void Episode::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}
void Episode::SetStage(int idx)
{
	currStage = stages[idx];

	int i = 0;
	vector<BackGround*>& backs = currStage->backs;
	for (auto& back : backs)
	{
		objList[LayerType::Back][i++].push_back(back);
	}


	currStage->SetAcitve(true);


	auto uimgr = (EpisodeUiMgr*)this->uiMgr;
	auto lastBotm = *(currStage->bottoms.end() - 1);
	auto firstBtom = *(currStage->bottoms.begin());
	float lb = lastBotm->GetGlobalBounds().left + lastBotm->GetGlobalBounds().width;
	float fb = firstBtom->GetGlobalBounds().left;;
	uimgr->setSpeed(lb - fb);
}

void Episode::test()
{
	float delta = worldView.getCenter().x;
	worldView.setCenter({ WINDOW_WIDTH/2.f,WINDOW_HEIGHT/2.f });
	for (auto& layer : objList)
	{
		for (auto& obj_pair : layer.second)
		{
			auto objs = obj_pair.second;
			for(auto& obj : objs)
				obj->Translate({ -delta,0 });
		}
	}
}

void Episode::CreateBottom(Vector2f pos, Stage* stage)
{
	bool draw = true;
	int cnt = stage->bottomArray.size();
	int idx = 1;
	auto btmCnt = stage->bottomArray;

	Vector2f currPos = pos;
	for(auto cols : btmCnt)
	{
		if (!draw)
		{
			currPos.x += cols * botmW;
			draw = !draw;
			continue;
		}

		VertexArrayObj* vaBottom = new VertexArrayObj();
		Vector2f drawPos = { currPos.x, WINDOW_HEIGHT - 100 };
		vaBottom->SetTexture(stage->bottomTex);

		objList[LayerType::Bottom][idx++].push_back(vaBottom);
		stage->bottoms.push_back(vaBottom);
		VertexArray& va = vaBottom->GetVA();

		va.setPrimitiveType(Quads);
		va.resize(cols  * 4);

		Vector2f offsets[4] = { {0,0}, {botmW,0}, {botmW,botmH}, {0,botmH} };
		Vector2f initPos = { 0, pos.y };
		for (int j = 0; j < cols; ++j)
		{
			int quadIndex = j;

			for (int k = 0; k < 4; ++k)
			{
				va[quadIndex * 4 + k].position = initPos + offsets[k];
				va[quadIndex * 4 + k].texCoords = offsets[k];
			}
			initPos.x += botmW;
		}

		currPos.x += cols * botmW;
		vaBottom->SetPos(drawPos);
		draw = !draw;
	}

}

void Episode::SetBackGround(Stage* prev, Stage* now)
{
	prev->SetBackGround((int)BackGround::BackState::Disable);
	now->SetBackGround((int)BackGround::BackState::Enable);
}

void Episode::SetIsFail(bool state)
{
	isFail = state;
	SCENE_MGR->GetCurrScene()->SetViewStop();
	((EpisodeUiMgr*)uiMgr)->setStop();
}

void Episode::SetTimeOut(bool state)
{
	isTimeOut = state;
	SCENE_MGR->GetCurrScene()->SetViewStop();
	((EpisodeUiMgr*)uiMgr)->setStop();
}

void Episode::SetScene(Scenes scene)
{
	if (scene == Scenes::EpisodeList)
	{
		SCENE_MGR->ChangeScene(Scenes::EpisodeList);
		//SCENE_MGR->ChangeScene(scene);
	}
	else if (scene == Scenes::Episode)
	{
		SCENE_MGR->ChangeScene(Scenes::EpisodeList);
		//Exit();
		//Enter();
	}
}

Vector2f Episode::GetCookiePos()
{
	return cookie->GetPos();
}

void Episode::CookieIsFail()
{
	cookie->Fail();
}

void Episode::AddPoint(int point)
{
	this->point += point;
	((EpisodeUiMgr*)uiMgr)->SetPoint(this->point);
}

void Stage::SetAcitve(bool active)
{
	for (BackGround* back : backs)
	{
		back->SetActive(active);
	}
	for (VertexArrayObj* bottom : bottoms)
	{
		bottom->SetActive(active);
	}
	for (Obstacle* obs : obstacles)
	{
		obs->SetActive(active);
	}
	for (Jelly* jel : jelly)
	{
		jel->SetActive(active);
	}
}

bool Stage::isEnd()
{
	VertexArrayObj* last = *(bottoms.end() - 1);
	auto bound = last->GetGlobalBounds();
	return bound.left + bound.width < WINDOW_WIDTH;
}

void Stage::Move()
{
	VertexArrayObj* last = *(bottoms.end() - 1);
	auto bound = last->GetGlobalBounds();
	for (auto bottom : bottoms)
	{
		bottom->Translate({ WINDOW_WIDTH, 0 });
	}
	for (auto obstacle : obstacles)
	{
		obstacle->Translate({WINDOW_WIDTH, 0});
	}
	for (auto jel : jelly)
	{
		jel->Translate({ WINDOW_WIDTH, 0 });
	}

}

void Stage::SetBackGround(int i)
{
	BackGround::BackState state = (BackGround::BackState)i;
	for (BackGround* back : backs)
	{
		back->SetBackgroundState(state);
	}
}
