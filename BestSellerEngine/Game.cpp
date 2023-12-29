#include "bsepch.h"

Game* Game::instance = nullptr;

Game* Game::GetInstance()
{
    static Game* instance = new Game;
    return instance;
}

void Game::Init() // TODO: Should not expect user to modify this...?
{
    engine = GameEngine::GetInstance();
    engine->Initialize();
    // Load levels below...?

    MainScene mainScene;
    mainScene.Init();
    mainScene.LoadGameObjects();
    mainScene.BuildHierarchy();
    
    std::vector<Scene*> Scenes{ &mainScene };
    engine->SetWorld(Scenes);

    engine->ChangeScene(&mainScene);
}

void Game::Run()
{
    while (engine->IsRunning())
    {
        engine->Update();
        engine->Draw();
        engine->PostUpdate();
    }
}

void Game::Reset()
{
    //TODO: Implement reset and test with many scenes
}

void Game::Quit()
{
    engine->Quit();
}