#pragma once
#include <string>
#include <SFML/Graphics.hpp>

#include <list>

using namespace std;
using namespace sf;


struct HitBox
{
	Vector2f initPos;
	Shape* shape;
	HitBox()
		:shape(nullptr) {}
	void SetPos(Vector2f pos)
	{
		shape->setPosition(pos + initPos);
	}
};

class Object
{
protected:
	int id;
	string name; //�ٸ� ������Ʈ�� �ߺ� ����
	bool enabled; //Ȱ��ȭ ���³� ��Ȱ��ȭ ���³� �װ��� �����δ�

	Vector2f position; //������ ������� �������� ������ ������ �־�� ��.
	float rotation;
	Vector2f scale;    //�θ��ڽ� ���� ���谡 �������� ������ �װ� �ϴ� �츮�� �����̳ʷ� ���� ����

	Vector2f initScale;

	vector<HitBox> hitBoxs;
	HitBox bottomHitBox;
public:
	Object();
	virtual ~Object();

	virtual bool GetActive() const;
	virtual void SetActive(bool active);

	virtual void Init();
	virtual void Release();

	virtual void SetPos(const Vector2f& pos);
	void Translate(const Vector2f& delta);
	virtual const Vector2f& GetPos() const;
	virtual void AddHitBox(RectangleShape hit, Vector2f pos, bool isBottom = false);
	virtual void AddHitBox(CircleShape hit, Vector2f pos, bool isBottom = false);
	virtual const vector<HitBox>* GetHitBox();
	virtual const HitBox& GetHitBoxBottom();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};