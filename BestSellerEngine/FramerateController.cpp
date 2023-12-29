#include "bsepch.h"

#define MILLISECOND 1000

FramerateController* FramerateController::instance = nullptr;

FramerateController* FramerateController::GetInstance()
{
	static FramerateController* instance = new FramerateController;
	return instance;
}

void FramerateController::Init()
{
	frameCount = 0;
}

void FramerateController::SetTargetFramerate(const float framerate)
{
	targetFrameTime = (int)(MILLISECOND / framerate);
}

void FramerateController::SetFrameAtLevelStart(const int time)
{
	frameAtLevelStart = time;
}

void FramerateController::FrameStart()
{
	timeAtFrameStart = glfwGetTime();
}

void FramerateController::FrameEnd()
{
	lastRenderTime = glfwGetTime() - timeAtFrameStart;

	timeAtFrameEnd = glfwGetTime();
	double delta = timeAtFrameEnd - timeAtFrameStart;
	double tt = (targetFrameTime / 1000);
	while (timeAtFrameEnd - timeAtFrameStart < tt)
	{
		timeAtFrameEnd = glfwGetTime();
	}

	++frameCount;

	lastFrameTime = timeAtFrameEnd - timeAtFrameStart;
	DeltaTime = (float)lastFrameTime;

	//std::cout << "Frames so far: " << frameCount << std::endl;
}

double FramerateController::GetFrameTime() const
{
	return lastFrameTime;
}

float FramerateController::GetFPS() const
{
	return (float)((1000 / lastFrameTime) / 1000);
}

int FramerateController::GetFrameNumber() const
{
	return frameCount;
}

void FramerateController::ResetFrameNumber()
{
	frameCount = 0;
}

double FramerateController::GetRenderTime() const
{
	return lastRenderTime;
}

double FramerateController::GetFrameAtLevelStart() const
{
	return frameAtLevelStart;
}

double FramerateController::GetTime() const
{
	return targetFrameTime;
}

double FramerateController::GetSeconds() const
{
	return glfwGetTime();
}
