#include "Scene.h"

Scene::Scene(Scenes type) :type(type)
{
}

Scene::~Scene()
{
}

void Scene::Update(float dt)
{
	for (auto& obj : objList)
	{
		if (obj->GetActive())
			obj->Update(dt);
	}
	for (auto& ui : uiObjList)
	{
		if (ui->GetActive())
			ui->Update(dt);
	}
}

void Scene::Draw(RenderWindow& window)
{
	for (auto& obj : objList)
	{
		if (obj->GetActive())
			obj->Draw(window);
	}
	for (auto& ui : uiObjList)
	{
		if (ui->GetActive())
			ui->Draw(window);
	}
}
