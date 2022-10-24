#include "Framework.h"
#include "info.h"
#include "InputMgr.h"
#include "../3rd/SingleTon.h"
#include "../Scens/SceneManager.h"
#include "ResourceManager.h"
#include "../DataTable/DataTableMGR.h"
#include "SoundManager.h"
#include "FileManager.h"


Framework::Framework()
    :timeScale(1.f)
{
    windowSize = { WINDOW_WIDTH, WINDOW_HEIGHT };
    window.create(VideoMode(windowSize.x, windowSize.y), "Game");
}

Framework::~Framework()
{
}

float Framework::GetDT() const
{
    return deltaTime.asSeconds() * timeScale;
}

float Framework::GetRealDT() const
{
    return deltaTime.asSeconds();
}

bool Framework::Init()
{
    FILE_MGR->LoadAll();
    RESOURCES_MGR->LoadAll();
    SOUND_MGR->Init();
    DATATABLE_MGR->Init();
    SCENE_MGR->Init();
    InputMgr::Init();
    
    return true;
}

bool Framework::Do()
{
    while (window.isOpen())
    {
        deltaTime = clock.restart();
        float dt = GetDT();
        InputMgr::ClearInput();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            InputMgr::UpdateInput(event);
        }

        window.clear();
        SCENE_MGR->Update(dt);
        SCENE_MGR->Draw(window);
        SOUND_MGR->Update();
        window.display();
    }

    return true;
}

#define DATATABLE_MGR (DataTableMgr::GetInstance())