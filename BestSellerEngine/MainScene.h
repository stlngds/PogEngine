#pragma once
#include "bsepch.h"

class MainScene : public Scene {
public:
	MainScene();
	~MainScene();
	void Update() override;
	void LateUpdate() override;

private:
	float vertx1 = 0.0f;
	float verty1 = 0.0f;
	float vertx2 = 0.0f;
	float verty2 = 0.0f;
};