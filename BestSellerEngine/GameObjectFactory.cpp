#include "bsepch.h"

GameObjectFactory* GameObjectFactory::instance = nullptr;

GameObjectFactory* GameObjectFactory::GetInstance()
{
	static GameObjectFactory* instance = new GameObjectFactory;
	return instance;
}

GameObjectFactory::~GameObjectFactory()
{

}

GameObject* GameObjectFactory::CreateGameObject(rapidjson::Value::ConstMemberIterator gameObjectIterator)
{
	//std::cout << gameObjectIterator->name.GetString() << std::endl;
	GameObject* go = new GameObject;
	go->SetName(gameObjectIterator->name.GetString());

	const rapidjson::Value& components = gameObjectIterator->value.FindMember("Components")->value;
	go->Deserialize(components);
	gameObjectDictionary[go->GetName()] = go;

	return go;
}

void GameObjectFactory::CreateAllGameObjects(std::string datasource)
{
	//::string fileName = "GameObjectsTest.json";
	FILE* fp;
	fopen_s(&fp, datasource.c_str(), "rb");
	if (!fp)
	{
		std::cout << "File doesn't exists or error reading." << std::endl;
		exit(EXIT_FAILURE);
	}

	char readBuffer[8192];
	rapidjson::FileReadStream inputStream(fp, readBuffer, sizeof(readBuffer));

	rapidjson::Document gameObjectDoc;
	gameObjectDoc.ParseStream(inputStream);

	const rapidjson::Value& gameObjects = gameObjectDoc.FindMember("GameObjects")->value;
	for (rapidjson::Value::ConstMemberIterator it = gameObjects.MemberBegin(); it != gameObjects.MemberEnd(); ++it)
		this->CreateGameObject(it);

	fclose(fp);
}

void GameObjectFactory::InitializeGameObjects()
{
	// After creating game objects, initialize them
	for (auto pair : gameObjectDictionary)
	{
		GameObject* go = pair.second;
		TransformComponent* trans = go->FindComponent<TransformComponent>();
		if (!trans)
		{
			std::cout << "Error: GameObject must have a transform component" << std::endl;
			exit(EXIT_FAILURE);
		}
		trans->Initialize();


		RenderComponent* rend = go->FindComponent<RenderComponent>();
		PhysicsComponent* phy = go->FindComponent<PhysicsComponent>();
		if (rend)	rend->Initialize();
		if (phy)	phy->Initialize();



	}

}

GameObject* GameObjectFactory::QuickFind(std::string name)
{
	GameObject* found = gameObjectDictionary.find(name)->second;
	return found;
}

void GameObjectFactory::AddForDeletion(GameObject* go)
{
	gameObjectsToDelete.push_back(go);
}

Node* GameObjectFactory::DeferredDeleteGameObjects(Node* node)
{
	Node* tmp = nullptr;
	// we don't want to traverse the whole list of children, because
	// in case we find the object we want to be deleted, then 
	// the traversal is over.

	// Step 1. Evaluate the current Node. Is it the one we want to delete?
	if (node->NeedsToBeDeleted())
	{
		node->Destroy();
		std::cout << node->GetName() << " completely destroyed!" << std::endl;

		delete node;
		node = nullptr;

		tmp = node;
		return tmp;
	}
	// Step 2. Traverse the children until find the wanted node
	auto& children = node->GetChildren();
	tmp = node;

	auto it = children.begin();
	while (it != children.end())
	{
		Node* deletedNode = this->DeferredDeleteGameObjects(*it);

		if (deletedNode == nullptr)
		{
			it = children.erase(it);
			continue;
		}
		it++;
	}
	/*for (auto it = children.begin(); it < children.end(); ++it)
	{
		Node* deletedNode = this->DeferredDeleteGameObjects(*it);

		if (deletedNode == nullptr)
		{
			it = children.erase(it);
		}

	}*/

	return tmp;
}

GameObject* GameObjectFactory::FindGameObjectinScene(Node* node, std::string nodeName)
{
	GameObject* go = nullptr;

	if (node->GetName() == nodeName)
	{
		go = dynamic_cast<GameObject*>(node);
		return go;
	}


	for (Node* node : node->GetChildren())
	{
		go = this->FindGameObjectinScene(node, nodeName);
		if (go)
			break;
	}


	return go;
}

void GameObjectFactory::ClearFactory()
{
	gameObjectDictionary.clear();

}

/*
void GameObjectFactory::AttachDebugQuad(GameObject* go, std::string quadName)
{
	DebugQuad* debugQuad = new DebugQuad;
	debugQuad->SetName(quadName); // the deletion of a quad is managed with deferred deletion, in the function DeferredDeleteGameObjects()
	go->AddChild(debugQuad);
}
*/

void GameObjectFactory::SetOneCollisionHandlerToAllPhysicsComponents(CollisionCallback callback)
{
	for (auto pair : gameObjectDictionary)
	{
		PhysicsComponent* phy = pair.second->FindComponent<PhysicsComponent>();
		if (phy)
			phy->SetCollisionCallback(callback);
	}
}