#include "bsepch.h"

GameObject::GameObject() : isAlive(true)
{
	this->toBeDeleted = false;
}

GameObject::~GameObject()
{

}

void GameObject::Initialize()
{
}

void GameObject::Update()
{
	if (!isAlive)
		return;

	std::vector<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		if (!*it)
			std::cout << "Component null in Game Object '" << this->name << "'" << std::endl;

		(*it)->Update();

		TransformComponent* transComp = this->FindComponent<TransformComponent>();
		if (transComp)
			Node::Update(); // Integrating the Scenegraph with our GameObject System


		it = it + 1;
	}

}

void GameObject::Shutdown()
{
	std::vector<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		(*it)->Shutdown();
		delete* it;
		it = it + 1;
	}
	components.clear();
}

void GameObject::HandleEvent(Event* evt)
{

	// first deal with the components of the object
	for (Component* component : components)
		component->HandleEvent(evt);

	// traverse the tree
	if (children.size() > 0)
		for (Node* object : children)
		{
			GameObject* go = dynamic_cast<GameObject*>(object);
			if (go)
				go->HandleEvent(evt);
		}


}

void GameObject::Deserialize(const rapidjson::Value& components)
{
	// loop through the components (each component)
	for (rapidjson::Value::ConstMemberIterator it = components.MemberBegin(); it != components.MemberEnd(); ++it)
	{
		std::string componentName = it->name.GetString();
		std::cout << "\t" << componentName << std::endl;
		if (componentName == GameObjectSystemComponentConstants::PHYSICS_COMPONENT) // hardcode because this is not handled by game developer (client)
		{
			const rapidjson::Value& componentMembers = it->value;
			PhysicsComponent* physicsComponent = this->AddComponent<PhysicsComponent>();
			physicsComponent->Deserialize(componentMembers);
		}
		if (componentName == GameObjectSystemComponentConstants::RENDER_COMPONENT) // hardcode because this is not handled by game developer (client)
		{
			const rapidjson::Value& componentMembers = it->value;
			RenderComponent* renderComponent = this->AddComponent<RenderComponent>();
			renderComponent->Deserialize(componentMembers);
		}
		if (componentName == GameObjectSystemComponentConstants::TRANSFORM_COMPONENT) // hardcode because this is not handled by game developer (client)
		{
			const rapidjson::Value& componentMembers = it->value;
			TransformComponent* transformComponent = this->AddComponent<TransformComponent>();
			transformComponent->Deserialize(componentMembers);
		}
	}
}

void GameObject::Draw()
{
	// We can do this because RenderComponent is a system level component, part of the Game Object system. Can be tightly coupled.
	RenderComponent* renderComp = this->FindComponent<RenderComponent>();

	if (!renderComp)
		return;
	renderComp->Draw();

	Node::Draw();
}

void GameObject::Destroy()
{
	Shutdown();

	Node::Destroy();
}

bool GameObject::IsAlive()
{
	return isAlive;
}

bool GameObject::MarkAsDelete()
{
	return toBeDeleted;
}

void GameObject::SetAlive(bool state)
{
	isAlive = state;
}

void GameObject::SetDelete(bool state)
{
	toBeDeleted = state;
}