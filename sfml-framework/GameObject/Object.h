#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Object
{
protected:
	int id;
	string name; //�ٸ� ������Ʈ�� �ߺ� ����
	bool enabled; //Ȱ��ȭ ���³� ��Ȱ��ȭ ���³� �װ��� �����δ�

	Vector2f position; //������ ������� �������� ������ ������ �־�� ��.
	float rotation;
	Vector2f scale;    //�θ��ڽ� ���� ���谡 �������� ������ �װ� �ϴ� �츮�� �����̳ʷ� ���� ����
public:
	Object();
	virtual ~Object();

	virtual bool GetActive() const;
	virtual void SetActive(bool active);

	virtual void Init();
	virtual void Release();

	virtual void SetPos(const Vector2f& pos);
	virtual const Vector2f& GetPos() const;

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};