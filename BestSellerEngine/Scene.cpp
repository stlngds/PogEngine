#include "bsepch.h"

Scene::Scene()
{
}


void Scene::Init()
{
	root = new Root;
	root->SetName("WorldOrigin");
	root->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	root->LoadPhysics();

	objectFactory = GameObjectFactory::GetInstance();
}

void Scene::LoadAssets()
{
	// Usually you would load here:
	// 1. All the textures data.
	// 2. All the models data.
	// 3. Store the above info in cache so that is used later when game objects load..
}

GameObject* Scene::GetGameObjectByName(std::string name)
{
	return objectFactory->FindGameObjectinScene(this->root, name);
}

void Scene::LoadGameObjects()
{
	// Here we load game objects
	objectFactory->CreateAllGameObjects(this->gameObjectsFile);
	objectFactory->InitializeGameObjects();

	// Add any general handling that you can here.
	objectFactory->SetOneCollisionHandlerToAllPhysicsComponents(this->callback); // still not the right place
}

void Scene::BuildHierarchy()
{
	// Building hierarchy from file, recursively
	FILE* fp;
	fopen_s(&fp, this->scenegraphFile.c_str(), "rb");
	if (!fp)
	{
		std::cout << "File doesn't exists or error reading." << std::endl;
		exit(EXIT_FAILURE);
	}

	char readBuffer[8192];
	rapidjson::FileReadStream inputStream(fp, readBuffer, sizeof(readBuffer));

	rapidjson::Document gameObjectDoc;
	gameObjectDoc.ParseStream(inputStream);

	const rapidjson::Value& nodes = gameObjectDoc.FindMember("root")->value;
	for (rapidjson::Value::ConstMemberIterator it = nodes.MemberBegin(); it != nodes.MemberEnd(); ++it)
		recursiveProcessNewChildren(it, root);



}

void Scene::UnloadAssets()
{
	// Clean all the garbage that game objects might have left. For example:
	// - Pointers to textures not treated (error handling)
	// - Images loaded in cache
	// - References to model files not cleaned properly when deleting the game objects
}

void Scene::Update()
{

	int x = -1;
	try
	{
		if (root == nullptr)
		{
			throw x;
		}
	}
	catch (int x)
	{
		std::cout << "Root is null!! :( " << std::endl;
	}

	if (root)
	{
		//std::cout << "Name of this root: " << this->root->GetName() << std::endl;
		this->root->GetTransform().SetTranslate(root->GetPhysicsBody()->Position);
		this->root->GetTransform().SetRotation(root->GetPhysicsBody()->Rotation);
		this->root->GetTransform().SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

		recursiveLevelUpdate(root); // Using a helper private function to execute recursion
		this->root->GetTransform().Compose(projection);

		inputActivity();

		this->root->Update();
	}


}

void Scene::LateUpdate()
{
	if (!this->root)
		return;

	// integration section
	PhysicsManager* physics = PhysicsManager::GetInstance();
	physics->ExecuteIntegrations();
	physics->EvaluateCollisions();
	physics->RegisterCollisionEvents();

	EventManager* eventManager = EventManager::GetInstance();
	eventManager->DispatchEvents(this->root); // Collision events. Needs ALL types of events. Including events for your input
	eventManager->FlushEvents();

	physics->FlushCollisions();

	flushDeadGameObjects();
}

void Scene::Draw()
{
	this->root->Draw();
}

void Scene::Destroy()
{
	root->Destroy();
	ServiceLocator::GetInstance()->EngineServices.GetFrameRateController()->ResetFrameNumber();
}

void Scene::Pause()
{
	// implement pause logic
}

void Scene::Resume()
{
	// implement resume logic
}

void Scene::flushDeadGameObjects()
{
	objectFactory->DeferredDeleteGameObjects(this->root);
}

void Scene::recursiveLevelUpdate(Node* node)
{
	if (!node)
		return;

	for (Node* go : node->GetChildren())
		recursiveLevelUpdate(go);

	GameObject* go = dynamic_cast<GameObject*>(node);
	if (!go)
		return;

	TransformComponent* trans = go->FindComponent<TransformComponent>();
	PhysicsComponent* phy = go->FindComponent<PhysicsComponent>();
	if (phy)
	{
		trans->SetPosition(phy->GetPosition());
		trans->SetRotation(phy->GetRotation());
	}
}

void Scene::recursiveProcessNewChildren(rapidjson::Value::ConstMemberIterator nodeIterator, Node* parent)
{
	std::string nodeName = nodeIterator->name.GetString();
	GameObject* newNode = objectFactory->QuickFind(nodeName);
	parent->AddChild(newNode);

	// add a debug quad only if in Debug mode &&  has a physics body 

	/*
	PhysicsComponent* phy = newNode->FindComponent<PhysicsComponent>();
	if (phy)
	{
		DebugQuad* debugQuad = new DebugQuad;
		debugQuad->SetName(nodeName.append("Quad"));
		debugQuad->SetScale(phy->GetScale());
		newNode->AddChild(debugQuad);
	}
	*/

	const rapidjson::Value& nodes = nodeIterator->value;

	if (nodes.IsObject())
	{
		for (rapidjson::Value::ConstMemberIterator it = nodes.MemberBegin(); it != nodes.MemberEnd(); ++it)
			recursiveProcessNewChildren(it, newNode); // newNode that comes from nodeIterator
	}


}

void Scene::inputActivity()
{
	/*
	InputManager* input = InputManager::GetInstance();
	// evaluate events triggered by any inputs. TODO: Implement Event system for input

	GameObject* MrTriangleObj = GetGameObjectByName("MrTriangleObj");
	if (MrTriangleObj)
	{
		if (input->IsKeyDown(UP))
			MrTriangleObj->FindComponent<PhysicsComponent>()->SetVelocity(
				glm::vec3(MrTriangleObj->FindComponent<TransformComponent>()->GetRotationMatrix() *
					MrTriangleObj->FindComponent<TransformComponent>()->GetScaleMatrix() *
					glm::vec4(0.0f, -2.0f, 0.0f, 1.0f)));

		if (input->IsKeyDown(DOWN))
			MrTriangleObj->FindComponent<PhysicsComponent>()->SetVelocity(
				glm::vec3(MrTriangleObj->FindComponent<TransformComponent>()->GetRotationMatrix() *
					MrTriangleObj->FindComponent<TransformComponent>()->GetScaleMatrix() *
					glm::vec4(0.0f, 2.0f, 0.0f, 1.0f)));

		if (input->IsKeyDown(LEFT))
			MrTriangleObj->FindComponent<PhysicsComponent>()->SetAngularVelocity(glm::vec3(0.0f, 0.0f, 2.0f));

		if (input->IsKeyDown(RIGHT))
			MrTriangleObj->FindComponent<PhysicsComponent>()->SetAngularVelocity(glm::vec3(0.0f, 0.0f, -2.0f));


	}
	*/
}