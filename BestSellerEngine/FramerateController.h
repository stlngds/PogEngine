#pragma once
class FramerateController
{
public:
	static FramerateController* GetInstance();
	~FramerateController();

	void Init();

	void SetTargetFramerate(const float framerate);
	void SetFrameAtLevelStart(const int time);
	void FrameStart();
	void FrameEnd();
	double GetFrameTime() const;
	float GetFPS() const;
	int GetFrameNumber() const;
	void ResetFrameNumber();
	double GetRenderTime() const;
	double GetFrameAtLevelStart() const;
	double GetTime() const;
	double GetSeconds() const;
	float DeltaTime;

private:

	FramerateController() {}
	static FramerateController* instance;

	int frameCount;
	double frameAtLevelStart;
	double timeAtFrameStart;
	double timeAtFrameEnd;
	double lastFrameTime;
	double lastRenderTime;
	double targetFrameTime;
};