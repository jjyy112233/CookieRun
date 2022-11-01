#pragma once
#include "../Button.h"

class SpriteObject;
enum class Scenes;
class Episode;
class GameEnd;
class GameEndButton : public Button
{
private:
	SpriteObject* btn;
	Episode* epi;
	Scenes scene;
	GameEnd* gameEnd;
public:
	void Set(Scenes scene, Episode* epi);
	void SetGameEnd(GameEnd* end) { gameEnd = end; }
	virtual void Init();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	virtual void SetPos(Vector2f pos);
	SpriteObject* GetSprite() { return btn; }
};

