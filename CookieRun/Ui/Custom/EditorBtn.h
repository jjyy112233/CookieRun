#pragma once
#include "../Button.h"

class SpriteObject;
class TextObject;
enum class Scenes;
class EditorBtn : public Button
{
private:
	SpriteObject* sprite;
	TextObject* txt;
	
	Scenes* scene;
	string episodeName;
public:
	EditorBtn(string episodeName);
	SpriteObject* GetSprite() { return sprite; }
	TextObject* GetText() { return txt; }
	virtual void SetPos(Vector2f pos);
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

