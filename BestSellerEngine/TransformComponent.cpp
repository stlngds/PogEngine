#include "bsepch.h"

TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::SetPosition(glm::vec3 position)
{
	GetOwner()->GetTransform().SetTranslate(position);
}

void TransformComponent::SetRotation(glm::vec3 eulerAngles)
{
	GetOwner()->GetTransform().SetRotation(eulerAngles);
}

void TransformComponent::SetScale(glm::vec3 nonUniformScale)
{
	GetOwner()->GetTransform().SetScale(nonUniformScale);
}

void TransformComponent::SetScale(float uniformScale)
{
	GetOwner()->GetTransform().SetScale(uniformScale);
}

glm::vec3 TransformComponent::GetPosition() const
{
	return GetOwner()->GetTransform().GetPosition();
}

glm::vec3 TransformComponent::GetOrientation() const
{
	return GetOwner()->GetTransform().GetRotationEulerAngles();
}

glm::vec3 TransformComponent::GetScale() const
{
	return GetOwner()->GetTransform().GetScaleVector();
}

glm::mat4 TransformComponent::GetTranslationMatrix() const
{
	return GetOwner()->GetTransform().GetTranslate();
}

glm::mat4 TransformComponent::GetRotationMatrix() const
{
	return GetOwner()->GetTransform().GetRotation();
}

glm::mat4 TransformComponent::GetScaleMatrix() const
{
	return GetOwner()->GetTransform().GetScale();
}

glm::mat4 TransformComponent::GetModelMatrix() const
{
	return GetOwner()->GetTransform().GetModelMatrix();
}

void TransformComponent::Initialize()
{
	GetOwner()->GetTransform().ResetModelMatrix();
}

void TransformComponent::Update()
{
	GetOwner()->GetTransform().Compose(glm::mat4(1.0f));
	/*if (GetOwner()->GetName() == "TriangleEnemy1")
	{
		std::cout << "Position in x of " << GetOwner()->GetName() << ": " << this->GetPosition().x << std::endl;
	}*/
}

void TransformComponent::Shutdown()
{
}

void TransformComponent::HandleEvent(Event* evt)
{
}

void TransformComponent::Deserialize(const rapidjson::Value& componentMembers)
{
	auto positionArray = componentMembers.FindMember(GameObjectSystemComponentConstants::POSITION_TRANS)->value.GetArray();
	auto rotationArray = componentMembers.FindMember(GameObjectSystemComponentConstants::ROTATION_TRANS)->value.GetArray();
	auto scaleArray = componentMembers.FindMember(GameObjectSystemComponentConstants::SCALE_TRANS)->value.GetArray();

	this->SetPosition(glm::vec3(positionArray[0].GetFloat(), positionArray[1].GetFloat(), positionArray[2].GetFloat()));
	this->SetRotation(glm::vec3(rotationArray[0].GetFloat(), rotationArray[1].GetFloat(), rotationArray[2].GetFloat()));
	this->SetScale(glm::vec3(scaleArray[0].GetFloat(), scaleArray[1].GetFloat(), scaleArray[2].GetFloat()));
}