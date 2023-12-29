#include "bsepch.h"

PhysicsComponent::PhysicsComponent() : physicsBody(nullptr)
{
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::SetPosition(glm::vec3 position)
{
	physicsBody->Position = position;
}

void PhysicsComponent::SetRotation(glm::vec3 rotation)
{
	physicsBody->Rotation = rotation;
}

void PhysicsComponent::SetScale(glm::vec3 scale)
{
	physicsBody->Scale = scale;
}

void PhysicsComponent::SetVelocity(glm::vec3 velocity)
{
	physicsBody->Velocity = velocity;
}

void PhysicsComponent::SetAcceleration(glm::vec3 acceleration)
{
	physicsBody->Acceleration = acceleration;
}

void PhysicsComponent::SetForce(glm::vec3 force)
{
	physicsBody->Force = force;
}

void PhysicsComponent::SetAngularVelocity(glm::vec3 angularVelocity)
{
	physicsBody->AngularVelocity = angularVelocity;
}

void PhysicsComponent::SetMass(float mass)
{
	physicsBody->Mass = mass;
}

void PhysicsComponent::SetInverseMass(float inverseMass)
{
	physicsBody->InverseMass = inverseMass;
}

void PhysicsComponent::Initialize()
{
	if (!physicsBody) // In case the body was already instantiated by the deserialization. If not, user is making the game object manually
		physicsBody = PhysicsManager::GetInstance()->BuildBody();


	PhysicsShapeType type = collisionData.shapeType; // Fed with a function for the client, or by the deserialization process.
	switch (type)
	{
	case CIRCLE:
		// TODO: Circles remain unimplemented at this time.
		break;
	case AABB_RECT:
	{
		AABB* aabb = dynamic_cast<AABB*>(PhysicsManager::GetInstance()->BuildShape(AABB_RECT));
		aabb->Left = -1.0f;
		aabb->Right = 1.0f;
		aabb->Top = 1.0f;
		aabb->Bottom = -1.0f;
		physicsBody->SetShape(aabb);
		physicsBody->Position = GetOwner()->GetTransform().GetPosition();
		//physicsBody->Scale = GetOwner()->GetTransform().GetScaleVector();
		break;
	}

	case OBB_RECT:
	{
		OBB* obb = dynamic_cast<OBB*>(PhysicsManager::GetInstance()->BuildShape(type));
		physicsBody->SetShape(obb);
		physicsBody->Position = GetOwner()->GetTransform().GetPosition();
		glm::vec3 rotation;
		glm::extractEulerAngleXYZ(GetOwner()->GetTransform().GetRotation(), rotation.x, rotation.y, rotation.z);
		physicsBody->Rotation = rotation;

		//physicsBody->Scale = GetOwner()->GetTransform().GetScaleVector();
		break;
	}
	case MAX_SHAPES:
		break;
	default:
		break;
	}
}

void PhysicsComponent::Update()
{
	if (physicsBody != nullptr)
	{
		// updates the physics body
		//physicsBody->Scale = GetOwner()->FindComponent<TransformComponent>()->GetScale();
		physicsBody->Update();
	}

}

void PhysicsComponent::Shutdown()
{
	PhysicsManager::GetInstance()->DisposeBody(this->physicsBody);
	delete physicsBody;
}

void PhysicsComponent::HandleEvent(Event* evt)
{
	CollisionEvent* collisionEvt = dynamic_cast<CollisionEvent*>(evt);
	//error handling
	if (!collisionEvt)
		return;

	Contact* contact = reinterpret_cast<Contact*>(static_cast<Event*>(collisionEvt)->GetUserData());

	if ((physicsBody == contact->Bodies[0]) || (physicsBody == contact->Bodies[1]))
	{
		//std::cout << "Ok, do something with " << GetOwner()->GetName() << " !!!" << std::endl;
		if (this->collisionData.callback)
			this->collisionData.callback(GetOwner());
	}
}

void PhysicsComponent::Serialize(std::string filename)
{
}

void PhysicsComponent::Deserialize(const rapidjson::Value& componentMembers)
{
	// properties
	auto position = componentMembers.FindMember(GameObjectSystemComponentConstants::POSITION)->value.GetArray();
	auto rotation = componentMembers.FindMember(GameObjectSystemComponentConstants::ROTATION)->value.GetArray();
	auto scale = componentMembers.FindMember(GameObjectSystemComponentConstants::SCALE)->value.GetArray();
	auto velo = componentMembers.FindMember(GameObjectSystemComponentConstants::VELOCITY)->value.GetArray();
	auto accl = componentMembers.FindMember(GameObjectSystemComponentConstants::ACCELERATION)->value.GetArray();
	auto forc = componentMembers.FindMember(GameObjectSystemComponentConstants::FORCE)->value.GetArray();
	auto angV = componentMembers.FindMember(GameObjectSystemComponentConstants::ANG_VELO)->value.GetArray();
	auto mass = componentMembers.FindMember(GameObjectSystemComponentConstants::MASS)->value.GetFloat();
	auto inv_mass = componentMembers.FindMember(GameObjectSystemComponentConstants::INV_MASS)->value.GetFloat();

	physicsBody = PhysicsManager::GetInstance()->BuildBody(); // Creates a Body object
	physicsBody->Position = glm::vec3(position[0].GetFloat(), position[1].GetFloat(), position[2].GetFloat());
	physicsBody->Rotation = glm::vec3(rotation[0].GetFloat(), rotation[1].GetFloat(), rotation[2].GetFloat());
	physicsBody->Scale = glm::vec3(scale[0].GetFloat(), scale[1].GetFloat(), scale[2].GetFloat());
	physicsBody->Velocity = glm::vec3(velo[0].GetFloat(), velo[1].GetFloat(), velo[2].GetFloat());
	physicsBody->Acceleration = glm::vec3(accl[0].GetFloat(), accl[1].GetFloat(), accl[2].GetFloat());
	physicsBody->Force = glm::vec3(forc[0].GetFloat(), forc[1].GetFloat(), forc[2].GetFloat());
	physicsBody->AngularVelocity = glm::vec3(angV[0].GetFloat(), angV[1].GetFloat(), angV[2].GetFloat());

	this->SetMass(mass);
	this->SetInverseMass(inv_mass);

	// body shapes
	int shapeType = componentMembers.FindMember(GameObjectSystemComponentConstants::SHAPE_TYPE)->value.GetInt();
	switch (shapeType)
	{
	case 0: collisionData.shapeType = CIRCLE; break;
	case 1: collisionData.shapeType = AABB_RECT; break;
	case 2: collisionData.shapeType = OBB_RECT; break;
	default: break;
	}

}

void PhysicsComponent::Integrate()
{
	if (physicsBody != nullptr)
		physicsBody->Integrate();
}

glm::vec3 PhysicsComponent::GetPosition()
{
	return physicsBody->Position;
}

glm::vec3 PhysicsComponent::GetRotation()
{
	return physicsBody->Rotation;
}

glm::vec3 PhysicsComponent::GetScale()
{
	return physicsBody->Scale;
}

void PhysicsComponent::SetCollisionCallback(CollisionCallback callbackFunction)
{
	this->collisionData.callback = callbackFunction;
}

void PhysicsComponent::SetCollisionShape(PhysicsShapeType shapeType)
{
	this->collisionData.shapeType = shapeType;
}
