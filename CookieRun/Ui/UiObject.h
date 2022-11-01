#pragma once
#include "../GameObject/Object.h"
	enum class UiState
	{
		None = -1, Enter, Stay, Down, Up, Exit
	};
class UiObject : public Object
{
public:
protected:
	bool isButton;
	FloatRect bound;

	UiState btnState;
	bool isEvent;

	bool (*isClick)();
public:
	UiObject();
	virtual ~UiObject();
	virtual void Init() override;
	virtual void Release()override;
	virtual void Reset()override;
	virtual void SetPos(const Vector2f& pos)override;
	virtual void Translate(const Vector2f& delta)override;

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	virtual bool IsDown() { return btnState == UiState::Down; }
	virtual bool IsUp() { return btnState == UiState::Up; }
	virtual bool IsEnter() { return btnState == UiState::Enter; }
	virtual bool IsExit() { return btnState == UiState::Exit; }
	virtual bool GetEvent() { if (!isButton) return false; return isEvent; }
	virtual UiState GetState() { return btnState; }

	void SetBound(FloatRect b) {
		bound = b; 
	}
	void SetButton(bool state) 
	{
		isButton = state; 
	}
};

