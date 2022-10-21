#include "Stage.h"
#include "../SceneManager.h"
#include "../../Framework/InputMgr.h"
#include "../../Framework/ResourceManager.h"
#include "../../GameObject/BackGround/BackGround.h"
#include "../../GameObject/TextObject.h"
#include "../../Framework/SoundManager.h"
#include "../../Framework/info.h"
#include "../../GameObject/VertexArrayObj.h"
#include "../../GameObject/Cookie/Cookie.h"

Stage::Stage()
	:Scene(Scenes::Episode1)
{
    botmW = 124.f;
    botmH = 200.f;
}

Stage::~Stage()
{
}

void Stage::Init()
{
	{
		BackGround* back = new BackGround(RESOURCES_MGR->GetTexture("graphics/episode1/s1-0.png"), 0.f);
		objList[LayerType::Back][0] = back;
		back = new BackGround(RESOURCES_MGR->GetTexture("graphics/episode1/s1-1.png"), 50.f);
		objList[LayerType::Back][1] = back;

        vector<int> btmCnt = { 10,1,10,1,10,1,10,1,10,1,5,2,5,2,5,2,10 };

        bottom = RESOURCES_MGR->GetTexture("graphics/episode1/s1-b.png");
        CreateBottom({ 0.f,0.f }, btmCnt, 1);

		cookie = new Cookie();
		objList[LayerType::Player][0] = cookie;
		cookie->Init();
	}
}

void Stage::Release()
{
}

void Stage::Enter()
{
	worldView.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	worldView.setCenter({ WINDOW_WIDTH/2,WINDOW_HEIGHT/2});
}

void Stage::Exit()
{

}

void Stage::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		SCENE_MGR->ChangeScene(Scenes::Episode2);
		return;
	}
	Scene::Update(dt);
}

void Stage::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}
void Stage::CreateBottom(Vector2f pos, vector<int> btmCnt, int rows)
{
	bool draw = true;
	int cnt = btmCnt.size();
	int idx = 1;
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
		vaBottom->SetTexture(bottom);

		objList[LayerType::Bottom][idx++] = vaBottom;
		bottoms.push_back(vaBottom);
		VertexArray& va = vaBottom->GetVA();
		va.setPrimitiveType(Quads);
		va.resize(cols * rows * 4);

		Vector2f offsets[4] = { {0,0}, {botmW,0}, {botmW,botmH}, {0,botmH} };
		for (int i = 0; i < rows; ++i)
		{
			Vector2f initPos = { 0, pos.y };
			for (int j = 0; j < cols; ++j)
			{
				int quadIndex = i * cols + j;

				for (int k = 0; k < 4; ++k)
				{
					va[quadIndex * 4 + k].position = initPos + offsets[k];
					va[quadIndex * 4 + k].texCoords = offsets[k];
				}
				initPos.x += botmW;
			}
		}

		currPos.x += cols * botmW;
		vaBottom->SetPos(drawPos);
		draw = !draw;
	}

}

