#pragma once
#include "bsepch.h"

class PhysicsManager {
public:
	static PhysicsManager* GetInstance();
	~PhysicsManager();

	void Init();

	Shape* BuildShape(PhysicsShapeType type);
	Body* BuildBody();
	void DestroyBody(Body* body);
	void EvaluateCollisions();
	void RegisterCollisionEvents();
	void ExecuteIntegrations();
	void FlushCollisions();
	void DisposeBody(Body* body);

	CollisionGenerator* collisionGenerator;

private:
	PhysicsManager() {}
	static PhysicsManager* instance;

	
	std::vector<Body*> bodies;
};

	/*
	class PhysicsManager {
	public:
		static PhysicsManager& GetInstance() {
			static PhysicsManager instance;
			return instance;
		}

		void AddObject(GameObject* object) {
			physicsObjects.push_back(object);
		}

		void Update(float deltaTime) {
			for (GameObject* object : physicsObjects) {
				if (object->GetPhysicsComponent()) {
					object->GetPhysicsComponent()->UpdatePhysics(deltaTime);
				}
			}
			HandleCollisions();
		}

	private:
		std::vector<GameObject*> physicsObjects;

		PhysicsManager() {}

		void HandleCollisions() {
			// TODO
		}

		PhysicsManager(const PhysicsManager&) = delete;
		PhysicsManager& operator=(const PhysicsManager&) = delete;
	};
	*/