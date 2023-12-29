#include "bsepch.h"

ServiceLocator* ServiceLocator::instance = nullptr;

ServiceLocator* ServiceLocator::GetInstance()
{
	static ServiceLocator* instance = new ServiceLocator;
	return instance;
}

WindowHandler& ServiceLocator::Services::GetWindow()
{
	return AWindow;
}

EventManager* ServiceLocator::Services::GetEventSystem()
{
	return Events;
}

/*
InputManager* ServiceLocator::Services::GetInput()
{
	return Input;
}
*/

PhysicsManager* ServiceLocator::Services::GetPhysicsSystem()
{
	return Physics;
}

FramerateController* ServiceLocator::Services::GetFrameRateController()
{
	return FrameRateController;
}

GameEngine* GameEngine::instance = nullptr;

GameEngine* GameEngine::GetInstance()
{
	static GameEngine* instance = new GameEngine;
	return instance;
}

void GameEngine::Initialize()
{
	// initialize all the rendering and windows and other subsystems
	serviceLocator = ServiceLocator::GetInstance();
	serviceLocator->EngineServices.GetWindow().Init();
	//serviceLocator->EngineServices.GetInput()->Init();
	serviceLocator->EngineServices.GetPhysicsSystem()->Init();
	serviceLocator->EngineServices.GetFrameRateController()->Init();
	serviceLocator->EngineServices.GetFrameRateController()->SetTargetFramerate(60.0);

	serviceLocator->EngineServices.GetFrameRateController()->SetFrameAtLevelStart(
		serviceLocator->EngineServices.GetFrameRateController()->GetFrameNumber());

	isRunning = true;
}

void GameEngine::Destroy()
{
	// destroy all references, window system and engine itself, including the stack of scenes
}

void GameEngine::SetWorld(std::vector<Scene*>& scenes)
{
	world.Scenes = scenes;
}

void GameEngine::ChangeScene(Scene* scene)
{
	if (!scenesStack.empty())
	{
		scenesStack.top()->Destroy();
		scenesStack.pop();
	}

	scenesStack.push(scene);

}

void GameEngine::PushScene(Scene* scene) // to keep the previous scene alive under a new one
{
	if (!scenesStack.empty())
		scenesStack.top()->Pause();

	scenesStack.push(scene);

}

void GameEngine::PopScene()
{
	if (!scenesStack.empty())
	{
		scenesStack.top()->Destroy();
		scenesStack.pop();

		scenesStack.top()->Resume();
	}
}

void GameEngine::HandleEvent(Event* evt)
{
	SceneChangeEvent* sceneEvent = static_cast<SceneChangeEvent*>(evt);
	if (!sceneEvent)
		return;

	if (world.Scenes.size() > 1)
		ChangeScene(world.Scenes[1]);
}

void GameEngine::Update()
{
	serviceLocator->EngineServices.GetFrameRateController()->FrameStart();

	serviceLocator->EngineServices.GetWindow().Update();
	ratio = serviceLocator->EngineServices.GetWindow().GetWindowBufferDimensions().x /
		(float)serviceLocator->EngineServices.GetWindow().GetWindowBufferDimensions().y;
	double x = (double)serviceLocator->EngineServices.GetWindow().GetWindowBufferDimensions().x;
	double y = (double)serviceLocator->EngineServices.GetWindow().GetWindowBufferDimensions().y;
	projection = glm::ortho(-x, x, -y, y, -1.0, 1.0);

	projection = glm::ortho(-640.0, 640.0, -480.0, 480.0, -1.0, 1.0);
	Scene* sc = scenesStack.top();
	
	sc->Update();
}

void GameEngine::Draw()
{

	int frameCount = serviceLocator->GetInstance()->EngineServices.GetFrameRateController()->GetFrameNumber();
	//std::cout << frameCount << std::endl;

	if (frameCount > 1)
		scenesStack.top()->Draw();
}

void GameEngine::PostUpdate()
{

	scenesStack.top()->LateUpdate();
	serviceLocator->EngineServices.GetWindow().SwapBuffers();
	//serviceLocator->EngineServices.GetInput()->PollEvents();
	serviceLocator->EngineServices.GetFrameRateController()->FrameEnd();
}

bool GameEngine::IsRunning()
{
	if (serviceLocator->EngineServices.GetWindow().ShouldClose())
		isRunning = false;

	return isRunning;
}

void GameEngine::Quit()
{
	serviceLocator->EngineServices.GetWindow().ShutDown();

	exit(EXIT_SUCCESS);
}