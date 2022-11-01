#pragma once
#include "../../Ui/Button.h"

class CustomSceneMgr;
class SpriteObject;
class LeftObject : public Button
{
private:
	SpriteObject* sprite;
	string id;
	CustomSceneMgr* mgr;
public:
	LeftObject(CustomSceneMgr* mgr);
	virtual ~LeftObject();
	virtual void SetTexture(Texture& tex);
	virtual void SetPos(Vector2f pos);
	virtual void SetSize(Vector2f size);
	virtual void SetScale(Vector2f scale);
	virtual void Init() override;
	void SetId(string id) { this->id = id; }
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual FloatRect GetGlobalBound();
	FloatRect GetLocalBound();
	bool isClick();
};

