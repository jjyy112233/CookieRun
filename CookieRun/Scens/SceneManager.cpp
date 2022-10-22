#include "SceneManager.h"
#include "episode/Episode.h"
#include "episode/Menu.h"
#include "../Framework/info.h"
#include "../Framework/ResourceManager.h"

Scene* SceneManager::GetCurrScene()
{
	return sceneMap[currScene];
}

Scene* SceneManager::GetScene(Scenes scene)
{
	return sceneMap[scene];
}

bool SceneManager::LoadPath()
{
	rapidcsv::Document doc(RESOURCES_MGR->FilePath, rapidcsv::LabelParams(0, -1));

	int col = doc.GetColumnCount();
	for (int i = 0; i < col; i++)
	{
		paths.push_back((doc.GetColumn<string>(1)[i]) + RESOURCES_CSV);
	}
	for (auto& path : paths)
	{
		PRINT(path);
	}
	return true;

}

bool SceneManager::Init()
{
	LoadPath();

	sceneMap[Scenes::Menu] = new Menu();
	sceneMap[Scenes::Episode1] = new Episode();
	sceneMap[Scenes::Episode2] = new Episode();
	sceneMap[Scenes::Episode3] = new Episode();

	//for (auto& scene : sceneMap)
	//{
	//	scene.second->Init();
	//}
	sceneMap[Scenes::Episode1]->Init();

	currScene = Scenes::Episode1;
	sceneMap[currScene]->Enter();
	return false;
}

void SceneManager::ChangeScene(Scenes scene)
{
	sceneMap[currScene]->Exit();
	currScene = scene;
	sceneMap[currScene]->Enter();
}

void SceneManager::Update(float dt)
{
	sceneMap[currScene]->Update(dt);
}

void SceneManager::Draw(RenderWindow& window)
{
	sceneMap[currScene]->Draw(window);
}
