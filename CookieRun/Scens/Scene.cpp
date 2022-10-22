#include "Scene.h"
#include <iostream>
#include "../GameObject/Object.h"
#include "../Framework/Framework.h"

Scene::Scene(Scenes type) :type(type), viewSpeed(500.f), initViewSpeed(500.f)
{
}

Scene::~Scene()
{
}

void Scene::SetViewStop()
{
	viewSpeed = 0.f;
}

void Scene::SetViewPlay()
{
	viewSpeed = initViewSpeed;
}

Vector2f Scene::ScreenToWorld(Vector2i screenPos)
{
	RenderWindow& window = FRAMEWORK->GetWindow();
	return window.mapPixelToCoords(screenPos, worldView);
}

Vector2f Scene::ScreenToUiPosition(Vector2i screenPos)
{
	RenderWindow& window = FRAMEWORK->GetWindow();
	return window.mapPixelToCoords(screenPos, uiView);
}
void Scene::Update(float dt)
{
	for (auto& layer : objList)
	{
		for (auto& obj_pair : layer.second)
		{
			auto obj = obj_pair.second;
			obj->Update(dt);
		}
	}

	for (auto& layer : uiObjList)
	{
		for (auto& ui_pair : layer.second)
		{
			auto ui = ui_pair.second;
			ui->Update(dt);
		}
	}


	worldView.setCenter(worldView.getCenter() + Vector2f{dt* viewSpeed, 0});

}

void Scene::Draw(RenderWindow& window)
{
	window.setView(worldView);
	for (auto& layer : objList)
	{
		for (auto& obj_pair : layer.second)
		{
			auto obj = obj_pair.second;
			obj->Draw(window);
		}
	}

	for (auto& layer : uiObjList)
	{
		for (auto& ui_pair : layer.second)
		{
			auto ui = ui_pair.second;
			ui->Draw(window);
		}
	}
}
