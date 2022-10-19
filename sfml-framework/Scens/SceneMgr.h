#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <map>
#include "../3rd/SingleTon.h"

using namespace std;
using namespace sf;
class SceneMgr : public Singleton<SceneMgr>
{
private:
	map<Scenes, Scene*> sceneMap;
	Scenes currScene;
public:
	Scenes GetCurrScene() const;
	Scene* GetScene(Scenes scene);
	bool Init();
	void ChangeScene(Scenes scene);
	void Update(float dt);
	void Draw(RenderWindow& window);
};

#define SCENE_MGR (SceneMgr::GetInstance())