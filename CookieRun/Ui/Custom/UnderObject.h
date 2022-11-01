#pragma once
#include "../../Ui/Button.h"
class SpriteObject;
class CustomSceneMgr;
class UnderObject : public Button
{
private:
	SpriteObject* sprite;
	CustomSceneMgr* mgr;
	bool isJelly;

public:
	UnderObject(CustomSceneMgr* mgr);
	virtual ~UnderObject();
	virtual void SetTexture(Texture& tex);
	virtual void SetPos(Vector2f pos);
	virtual void SetSize(Vector2f size);
	virtual void SetScale(Vector2f scale);
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual FloatRect GetGlobalBound();
	FloatRect GetLocalBound();

	void SetIsJelly(bool state) { isJelly = state; }
	bool GetIsJelly() { return isJelly; }

	SpriteObject* GetSprite() { return sprite; }
};

