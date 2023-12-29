#pragma once
#include "bsepch.h"

class ServiceLocator
{

private:
	ServiceLocator() {}
	static ServiceLocator* instance;

	struct Services
	{
	public:
		WindowHandler& GetWindow();
		EventManager* GetEventSystem();
		//InputManager* GetInput();
		PhysicsManager* GetPhysicsSystem();
		FramerateController* GetFrameRateController();

	private:
		// Init Window System
		WindowHandler& AWindow = WindowHandler::GetInstance();

		// Init Event System
		EventManager* Events = EventManager::GetInstance();

		// Init Input System
		//InputManager* Input = InputManager::GetInstance();

		// Init Physics System
		PhysicsManager* Physics = PhysicsManager::GetInstance();

		// Framerate Controller 
		FramerateController* FrameRateController = FramerateController::GetInstance();

	};


public:
	static ServiceLocator* GetInstance();
	~ServiceLocator() {}

	Services EngineServices;




};

class GameEngine {
public:
	static GameEngine* GetInstance();
	~GameEngine();


	void Initialize();
	void Destroy();


	void SetWorld(std::vector<Scene*>& scenes);
	void ChangeScene(Scene* scene);
	void PushScene(Scene* scene);
	void PopScene();

	void HandleEvent(Event* evt);
	void Update();
	void Draw();
	void PostUpdate();

	bool IsRunning();
	void Quit();

private:

	GameEngine() {}
	static GameEngine* instance;

	std::stack<Scene*> scenesStack;
	bool isRunning;

	ServiceLocator* serviceLocator;
	float ratio;

	struct World
	{
		std::vector<Scene*> Scenes;
	};

	World world;
};

class SceneChangeEvent : public Event
{
public:
	SceneChangeEvent() {}
	~SceneChangeEvent() {}
};