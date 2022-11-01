#include "UiMgr.h"
#include "../Ui/UiObject.h"
#include <iostream>

UiMgr::UiMgr(Scene* scene) : parentScene(scene), enabled(true)
{
}

UiMgr::~UiMgr()
{
   // Release();
}

void UiMgr::Init()
{
    for (auto& uiObjs : uiObjList)
    {
        for (auto& obj : uiObjs.second)
            obj->Init();
    }
	Object::Init();
}

void UiMgr::Release()
{
    //for (auto& uiObjs : uiObjList)
    //{
    //    for (auto& obj : uiObjs.second)
    //    {
    //        if (obj != nullptr)
    //        {
    //            obj->Release();
    //            delete obj;
    //            obj = nullptr;
    //        }
    //    }
    //    uiObjs.second.clear();
    //}
    //uiObjList.clear();
    //Object::Release();
    //parentScene = nullptr;
}



void UiMgr::SetPos(const Vector2f& pos)
{
    Vector2f delta = pos - position;
    for (auto& uiObjs : uiObjList)
    {
        for (auto& obj : uiObjs.second)
            obj->Translate(delta);
    }
    position = pos;
    Object::SetPos(pos);
}

void UiMgr::Update(float dt)
{
    if (!enabled)
        return;

    for (auto& uiObjs : uiObjList)
    {
        for (auto& uiObj : uiObjs.second)
        {
            //bool t = uiObj->GetEvent();
            uiObj->Update(dt);
            //if (t)
            //    return;
        }
        
        //for (auto it = uiObjs.second.rbegin(); it != uiObjs.second.rend(); it++)
        //{
        //    bool t = (*it)->GetEvent();
        //    (*it)->Update(dt);
        //    if (t)
        //        return;
        //    if (parentScene == nullptr)
        //        return;
        //}
    }

}

void UiMgr::Draw(RenderWindow& window)
{
    if (!enabled)
        return;
    for (auto& uiObjs : uiObjList)
    {
        for (auto& obj : uiObjs.second)
            obj->Draw(window);
    }
}
