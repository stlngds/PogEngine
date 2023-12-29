#pragma once
#include "bsepch.h"

class Game
{
public:
	static Game* GetInstance();
	~Game() {}

	void Init();
	void Run();
	void Reset();
	void Quit();

private:
	Game() {}
	static Game* instance;

	GameEngine* engine;
};