#include "bsepch.h"

void CollisionGenerator::RegisterCollisionTests(PhysicsShapeType bodyType1, PhysicsShapeType bodyType2, CollisionTest fn) {
	CollisionTable[bodyType1][bodyType2] = fn;
}

bool CollisionGenerator::GenerateContacts(Shape* a, glm::vec3 aPos, Shape* b, glm::vec3 bPos, Contact* contact)
{
 	return (*CollisionTable[a->GetType()][b->GetType()])(a, aPos, b, bPos, contact);
}

void CollisionGenerator::ClearContacts()
{
	contacts.clear();
}

void CollisionGenerator::RegisterContact(Contact* contact)
{

	// check if there is a contact that already includes the 2 bodies
	// if that happens, don't register the contact.
	auto it = std::find_if(contacts.begin(), contacts.end(), ValidateContactBodies(contact)); //O(N) = be careful!
	if (it == contacts.end())
		contacts.push_back(contact);

}

std::vector<Contact*>* CollisionGenerator::GetContactsReference()
{
	return &contacts;
}

bool ValidateContactBodies::operator()(Contact* c1) const
{
	Body* c1_body1 = c1->Bodies[0];
	Body* c1_body2 = c1->Bodies[1];

	Body* c2_body1 = contact->Bodies[0];
	Body* c2_body2 = contact->Bodies[1];

	if (c1_body1 == c2_body1 && c1_body1 == c2_body2)
		return true;

	if (c1_body2 == c2_body1 && c1_body1 == c2_body2)
		return true;

	return false;
}
