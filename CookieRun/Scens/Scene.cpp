#include "Scene.h"
#include <iostream>
#include "../GameObject/Object.h"
#include "../Framework/Framework.h"

Scene::Scene(Scenes type) :type(type), viewSpeed(800.f), initViewSpeed(500.f)
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
			auto objs = obj_pair.second;

			for (auto& obj : objs)
			{
				if (obj->GetActive())
				{
					obj->Update(dt);
					if (layer.first == LayerType::Cookie)
						continue;
					obj->Translate(Vector2f{ -1.f,0 } * viewSpeed * dt);
				}
			}
		}
	}

	for (auto& layer : uiObjList)
	{
		for (auto& ui_pair : layer.second)
		{
			auto uis = ui_pair.second;
			for (auto& ui : uis)
			{
				if(ui->GetActive())
					ui->Update(dt);
			}
		}
	}
}

void Scene::Draw(RenderWindow& window)
{
	window.setView(worldView);
	for (auto& layer : objList)
	{
		for (auto& obj_pair : layer.second)
		{
			auto objs = obj_pair.second;
			for (auto& obj : objs)
			{
				if (obj->GetActive())
				{
					obj->Draw(window);
				}
			}
		}
	}

	for (auto& layer : uiObjList)
	{
		for (auto& ui_pair : layer.second)
		{
			auto uis = ui_pair.second;
			for (auto& ui : uis)
			{
				if (ui->GetActive())
				{
					ui->Draw(window);
				}
			}
		}
	}
}
