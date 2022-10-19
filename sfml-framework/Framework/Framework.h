#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
// Framework는 새로 만드는 게임마다 상속 받게 됨
class Framework 
{
protected:
	RenderWindow window;
	Vector2i windowSize;
	Clock clock;
	Time deltaTime;
	float timeScale;

public:
	Framework(int width, int height);
	virtual ~Framework();

	float GetDT() const;
	float GetRealDT() const;

	bool Init();
	bool Do();
};
