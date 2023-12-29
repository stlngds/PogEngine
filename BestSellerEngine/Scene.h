#pragma once
#include "bsepch.h"
class Scene
{
public:
	Scene();
	~Scene() {}

	void LoadAssets();
	void LoadGameObjects();
	void BuildHierarchy();
	void UnloadAssets();

	void Init();
	virtual void Update();
	virtual void LateUpdate();
	void Draw();
	void Destroy();

	void Pause();
	void Resume();

	GameObject* GetGameObjectByName(std::string name);// you can add another function GetGameObjectById(int id);

private:

	void flushDeadGameObjects();
	void recursiveLevelUpdate(Node* node);
	void recursiveProcessNewChildren(rapidjson::Value::ConstMemberIterator nodeIterator, Node* parent);

	// input feature, will be moved to a client's component
	void inputActivity();

protected:
	Root* root; // Composition
	GameObjectFactory* objectFactory;  // Aggregation
	CollisionCallback callback;
	std::string gameObjectsFile;
	std::string scenegraphFile;
};