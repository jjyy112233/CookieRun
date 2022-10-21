#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <map>
#include <string>

using namespace sf;
using namespace std;

class Object;
enum class Scenes
{
	None = -1, Menu,Episode1,Episode2,Episode3, Count
};
enum class LayerType
{
	None, Back,Bottom, Object, Player, Pet, UI
};
class Scene
{
protected:
	Scenes type;

	map<LayerType, map<int, Object*>> objList;
	map<LayerType, map<int, Object*>> uiObjList;

	View worldView;
	View uiView;

	float viewSpeed;

public:
	Scene(Scenes type);
	virtual ~Scene();

	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Init() = 0;
	virtual void Release() = 0;

	View& GetWorldView() { return worldView; }
	View& GetUiView() { return uiView; }

	Vector2f ScreenToWorld(Vector2i screenPos);
	Vector2f ScreenToUiPosition(Vector2i screenPos);

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};

