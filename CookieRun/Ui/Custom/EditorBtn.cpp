#include "EditorBtn.h"
#include "../../GameObject/SpriteObject.h"
#include "../../Scens/Scene.h"
#include "../../Scens/SceneManager.h"
#include "../../GameObject/TextObject.h"
#include <iostream>

EditorBtn::EditorBtn(string episodeName)
	: episodeName(episodeName)
{
	SetButton(true);
	sprite = new SpriteObject();
	txt = new TextObject();
}


void EditorBtn::SetPos(Vector2f pos)
{
	sprite->SetPos(pos);
	txt->SetPosition(pos + Vector2f{-0,-15});
	SetBound(sprite->GetGlobalBound());
	Button::SetPos(pos);
}

void EditorBtn::Update(float dt)
{
	Button::Update(dt);

	if (IsUp())
	{
		SCENE_MGR->ChangeEditor(episodeName);
	}
	if (IsEnter())
	{
		sprite->SetColor(Color(200, 200, 200, 255));
	}
	if (IsExit())
	{
		sprite->SetColor(Color::White);
	}
}

void EditorBtn::Draw(RenderWindow& window)
{
	sprite->Draw(window);
	txt->Draw(window);
}
