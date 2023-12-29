#pragma once
#include "bsepch.h"

class Contact {
public:
	Contact() {}
	~Contact() {}

	std::array<Body*, 2> Bodies;
};

class ValidateContactBodies {
public:
	ValidateContactBodies(Contact* contact) : contact(contact) {}

	bool operator()(Contact* c1) const;

private:
	Contact* contact;
};

typedef bool(*CollisionTest)(
	Shape* shape1, glm::vec3 posShape1, Shape* shape2, glm::vec3 posShape2, Contact* contacts);

class CollisionGenerator {
public:
	CollisionGenerator() {}
	~CollisionGenerator() {}

	void RegisterCollisionTests(PhysicsShapeType bodyType1, PhysicsShapeType bodyType2, CollisionTest fn);
	bool GenerateContacts(Shape* a, glm::vec3 aPos, Shape* b, glm::vec3 bPos, Contact* contact);
	void ClearContacts();
	void RegisterContact(Contact* contact);
	std::vector<Contact*>* GetContactsReference();

private:
	CollisionTest CollisionTable[MAX_SHAPES][MAX_SHAPES];
	std::vector<Contact*> contacts;
};