#pragma once
#include "../UiMgr.h"

class MenuButton;
class Scene;
class MenuUiMgr : public UiMgr
{
private:
	MenuButton* startBtn;
public:
	MenuUiMgr(Scene* scene);
	virtual void Update(float dt) override;
	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	void ClickStartBtn();
};

