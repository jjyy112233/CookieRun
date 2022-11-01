#include "SceneManager.h"
#include "episode/Episode.h"
#include "customScene/CustomScene.h"
#include "episode/Menu.h"
#include "episode/Ready.h"
#include "episode/EpisodeChoice.h"
#include "customScene/EditorChoice.h"
#include "../Framework/info.h"
#include "../Framework/ResourceManager.h"
#include "../Framework/InputMgr.h"

SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::Release()
{
	for (auto& scene : sceneMap)
	{
		delete scene.second;
	}
}

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
	sceneMap[Scenes::Ready] = new Ready();
	sceneMap[Scenes::Editor] = new CustomScene();
	sceneMap[Scenes::EpisodeList] = new EpisodeChoice();
	sceneMap[Scenes::Episode] = new Episode("config/data/episode.json");
	sceneMap[Scenes::EditorList] = new EditorChoice();

	currScene = Scenes::Menu;
	sceneMap[currScene]->Enter();
	return false;
}

void SceneManager::ChangeScene(Scenes scene)
{
	InputMgr::Clear();
	sceneMap[currScene]->Exit();
	currScene = scene;
	sceneMap[currScene]->Enter();
}

void SceneManager::ChangeEpisode(string name)
{
	((Episode*)sceneMap[Scenes::Episode])->SetEiosodeName(name);
	sceneMap[Scenes::Episode]->Exit();
	currScene = Scenes::Episode;
	sceneMap[Scenes::Episode]->Enter();
}
void SceneManager::ChangeEditor(string name)
{
	((CustomScene*)sceneMap[Scenes::Editor])->SetEiosodeName(name);
	
	sceneMap[Scenes::Editor]->Exit();
	currScene = Scenes::Editor;
	sceneMap[Scenes::Editor]->Enter();
}

void SceneManager::Update(float dt)
{
	sceneMap[currScene]->Update(dt);
}

void SceneManager::Draw(RenderWindow& window)
{
	sceneMap[currScene]->Draw(window);
}
