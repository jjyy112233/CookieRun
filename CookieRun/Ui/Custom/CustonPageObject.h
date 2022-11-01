#pragma once
#include "../UiObject.h"
class SpriteObject;
class CustomSceneMgr;
class CustomPage;
class CustonPageObject : public UiObject
{
private:
	CustomPage* page;
	SpriteObject* sprite;
	string id;

	bool isJelly;
public:
	CustonPageObject();
	virtual ~CustonPageObject();
	virtual void SetTexture(Texture& tex);
	virtual void SetPos(const Vector2f& pos) override;
	virtual void Translate(const Vector2f& delta)override;
	virtual void SetSize(Vector2f size);
	virtual void SetScale(Vector2f scale);
	virtual void Init() override;
	void SetId(string id) { this->id = id; }
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual FloatRect GetGlobalBound();
	FloatRect GetLocalBound();
	SpriteObject* GetSprite() { return sprite; }
	bool isClick();
	void SetPage(CustomPage* page);

	virtual void Release() override;
	void SetJelly(bool state) { isJelly = state; }
	bool GetJelly() { return isJelly; }
};

