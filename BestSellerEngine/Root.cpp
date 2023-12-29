#include "bsepch.h"


std::vector<GameObject*> Root::GetRoots()
{
	std::vector<GameObject*> rootChildren;
	for (Node* node : children)
		rootChildren.push_back(static_cast<GameObject*>(node));
	return rootChildren;
}

void Root::LoadPhysics()
{
	physicalBody = PhysicsManager::GetInstance()->BuildBody();
	physicalBody->SetShape(nullptr);
	physicalBody->Position = this->GetTransform().GetPosition();
	physicalBody->Scale = this->GetTransform().GetScaleVector();
}

void Root::UpdatePhysics()
{
	if (physicalBody != nullptr)
	{
		// updates the physics body
		glm::vec3 scaleVector = this->GetTransform().GetScaleVector();
		physicalBody->Scale = scaleVector;
		physicalBody->Update();
	}
}