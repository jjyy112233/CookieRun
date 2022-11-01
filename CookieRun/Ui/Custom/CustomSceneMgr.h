#pragma once
#include "../UiMgr.h"

class LeftUi;
class UderUi;
class CustomPage;
class UnderObject;
class CustomSceneMgr : public UiMgr
{
private:
	LeftUi* left;
	UderUi* under;
	CustomPage* page;

	string nowObj;
	bool nowObjIsJelly;
	UnderObject* drawObj;
	map<string, Vector2f> drawPos;
	int greed;

public:
	CustomSceneMgr(Scene* scene);
	~CustomSceneMgr();
	void SetPage(string id);
	void SetObj(string obj, bool isJelly = false);
	void AddObj(Vector2f pos);
	virtual void Update(float dt);
	void Save();
	void Init();
};

