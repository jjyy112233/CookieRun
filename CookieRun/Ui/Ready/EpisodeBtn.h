#pragma once
#include "../Button.h"

class SpriteObject;
class TextObject;
enum class Scenes;
class EpisodeBtn : public Button
{
private:
	SpriteObject* sprite;
	TextObject* txt;
	
	Scenes* scene;
	string episodeName;
public:
	EpisodeBtn(string episodeName);
	SpriteObject* GetSprite() { return sprite; }
	TextObject* GetText() { return txt; }
	virtual void SetPos(Vector2f pos);
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

