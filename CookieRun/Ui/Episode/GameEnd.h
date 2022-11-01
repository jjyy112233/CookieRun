#pragma once
#include "../UiObject.h"

class GameEndButton;
class SpriteObject;
class TextObject;
enum class Scenes;
class GameEnd : public UiObject
{
private:
	SpriteObject* back;
	//GameEndButton* retry;
	GameEndButton* epiList;
	TextObject* txt;
	Scenes nextScene;
	bool isClick;
public:
	virtual void Init();
	virtual void Release() override;
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	void SetScene(Scenes scene);
	virtual void SetPoint(string str);
};

