#pragma once
#include "bsepch.h"

typedef void (*CollisionCallback)(GameObject* go);


class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);
	void SetScale(glm::vec3 scale);
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();


	void SetVelocity(glm::vec3 velocity);
	void SetAcceleration(glm::vec3 acceleration);
	void SetForce(glm::vec3 force);
	void SetAngularVelocity(glm::vec3 angularVelocity);
	void SetMass(float mass);
	void SetInverseMass(float inverseMass);

	void Initialize();
	void Update();
	void Shutdown();
	void HandleEvent(Event* evt);
	void Serialize(std::string filename);
	void Deserialize(const rapidjson::Value& componentMembers);

	void Integrate();

	void SetCollisionCallback(CollisionCallback callbackFunction);
	void SetCollisionShape(PhysicsShapeType shapeType);

	Body* physicsBody; // was private

private:
	struct CollisionData
	{
		CollisionCallback callback;
		PhysicsShapeType shapeType;
	};

	

	CollisionData collisionData;
};