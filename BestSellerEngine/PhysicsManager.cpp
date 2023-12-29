#include "bsepch.h"

PhysicsManager* PhysicsManager::instance = nullptr;

PhysicsManager::~PhysicsManager() {
	delete collisionGenerator;
	delete instance;
}

void PhysicsManager::Init() {
	collisionGenerator = new CollisionGenerator;

	collisionGenerator->RegisterCollisionTests(AABB_RECT, AABB_RECT, CollisionFunctions2D::CheckCollisionAABBAABB);
	collisionGenerator->RegisterCollisionTests(AABB_RECT, CIRCLE, CollisionFunctions2D::CheckCollisionAABBCircle);
	collisionGenerator->RegisterCollisionTests(AABB_RECT, OBB_RECT, CollisionFunctions2D::CheckCollisionAABBOBB);

	collisionGenerator->RegisterCollisionTests(CIRCLE, AABB_RECT, CollisionFunctions2D::CheckCollisionCircleAABB);
	collisionGenerator->RegisterCollisionTests(CIRCLE, CIRCLE, CollisionFunctions2D::CheckCollisionCircleCircle);
	collisionGenerator->RegisterCollisionTests(CIRCLE, OBB_RECT, CollisionFunctions2D::CheckCollisionCircleOBB);

	collisionGenerator->RegisterCollisionTests(OBB_RECT, AABB_RECT, CollisionFunctions2D::CheckCollisionOBBAABB);
	collisionGenerator->RegisterCollisionTests(OBB_RECT, CIRCLE, CollisionFunctions2D::CheckCollisionOBBCircle);
	collisionGenerator->RegisterCollisionTests(OBB_RECT, OBB_RECT, CollisionFunctions2D::CheckCollisionOBBOBB);
}

PhysicsManager* PhysicsManager::GetInstance() {
	static PhysicsManager* instance = new PhysicsManager;
	return instance;
}

Shape* PhysicsManager::BuildShape(PhysicsShapeType type) {
	switch (type) {
	case CIRCLE: return nullptr;
	case AABB_RECT: {
		AABB* aabb = new AABB;
		aabb->SetType(type);
		return aabb;
	}
	case OBB_RECT: {
		OBB* obb = new OBB;
		obb->SetType(type);
		return obb;
	}
	default: return nullptr;
	}
}

Body* PhysicsManager::BuildBody() {
	Body* body = new Body;
	body->Init();
	bodies.push_back(body);
	return body;
}

void PhysicsManager::DestroyBody(Body* body) {
	delete body;
}

void PhysicsManager::EvaluateCollisions() {
	for (Body* body1 : bodies) {
		if (!body1) continue;
		if (!body1->GetShape()) continue;

		for (Body* body2 : bodies) {
			if (!body2) continue;
			if (!body2->GetShape()) continue;
			if (body1 == body2) continue;
			
			Contact* contact = new Contact;
			if (collisionGenerator->GenerateContacts(body1->GetShape(), body1->Position, body2->GetShape(), body2->Position, contact)) {
				contact->Bodies[0] = body1;
				contact->Bodies[1] = body2;
				collisionGenerator->RegisterContact(contact);
			}
		}
	}
}

void PhysicsManager::RegisterCollisionEvents()
{
	for (Contact* contact : *collisionGenerator->GetContactsReference())
	{
		CollisionEvent* evt = new CollisionEvent;
		evt->SetUserData(contact);
		EventManager::GetInstance()->RegisterEvent(evt);
	}
}

void PhysicsManager::ExecuteIntegrations()
{
	for (Body* body : bodies)
	{
		if (!body)	continue;
		body->Integrate();
	}
}

void PhysicsManager::FlushCollisions()
{
	for (Contact* contact : *collisionGenerator->GetContactsReference())
	{
		contact->Bodies[0] = nullptr;
		contact->Bodies[1] = nullptr;
	}
	collisionGenerator->ClearContacts();
}

void PhysicsManager::DisposeBody(Body* body)
{
	for (auto it = bodies.begin(); it < bodies.end(); ++it)
	{
		if ((*it) == body)
		{
			it = bodies.erase(it);
			return;
		}
	}
}
