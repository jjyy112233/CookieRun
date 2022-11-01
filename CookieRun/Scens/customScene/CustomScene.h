#pragma once
#include "../../Scens/Scene.h"

class SpriteObject;
class CustomScene : public Scene
{
private:
	string name;
public:
	CustomScene();
	~CustomScene();
	virtual void Update(float dt) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Init() override;
	virtual void Release() override;
	void SetEiosodeName(string str) { name = str; }
};

