#pragma once
#include "Object.h"
#include "../Framework/Utils.h"

class SpriteObject : public Object
{
protected:
	Sprite sprite;
public:
	SpriteObject();
	virtual ~SpriteObject();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	virtual void SetScale(Vector2f scale);
	virtual void SetPos(Vector2f pos);

	void Translate(const Vector2f& delta);

	void SetTexture(Texture& tex);
	void SetOrigin(Origins origin);
};

