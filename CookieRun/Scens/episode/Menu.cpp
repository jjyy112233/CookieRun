#include "Menu.h"
#include "../SceneManager.h"
#include "../../Framework/InputMgr.h"
#include "../../Framework/ResourceManager.h"
#include "../../GameObject/SpriteObject.h"
#include "../../GameObject/TextObject.h"
#include "../../Framework/Utils.h"

Menu::Menu()
	:Scene(Scenes::Menu)
{

}

Menu::~Menu()
{
}

void Menu::Init()
{
}

void Menu::Release()
{
}

void Menu::Enter()
{

}

void Menu::Exit()
{
}

void Menu::Update(float dt)
{
	Scene::Update(dt);
}

void Menu::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}
