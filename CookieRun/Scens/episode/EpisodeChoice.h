#pragma once
#include "../Scene.h"
#include "../../Ui/Ready/EpisodeBtn.h"
class EpisodeChoice : public Scene
{
private:

public:
	EpisodeChoice();
	// Scene을(를) 통해 상속됨
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};

