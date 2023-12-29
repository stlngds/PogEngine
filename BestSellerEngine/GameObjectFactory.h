#pragma once
#include "bsepch.h"
class GameObjectFactory
{
public:
	static GameObjectFactory* GetInstance();
	~GameObjectFactory();

	GameObject* CreateGameObject(rapidjson::Value::ConstMemberIterator member);
	void CreateAllGameObjects(std::string datasource);
	void InitializeGameObjects();
	GameObject* QuickFind(std::string name);
	void AddForDeletion(GameObject* go);
	void ClearFactory();

	// Mark this function only for debug build
	//void AttachDebugQuad(GameObject* go, std::string quadName);

	// Just a helper function for teaching. Should not be like this
	void SetOneCollisionHandlerToAllPhysicsComponents(CollisionCallback callback);

	// Move these functions to a proper scene / level manager
	Node* DeferredDeleteGameObjects(Node* node);
	GameObject* FindGameObjectinScene(Node* node, std::string nodeName);


private:
	GameObjectFactory() {}
	static GameObjectFactory* instance;

	std::unordered_map<std::string, GameObject*> gameObjectDictionary; // Find in O(1)
	std::vector<GameObject*> gameObjectsToDelete;
};

