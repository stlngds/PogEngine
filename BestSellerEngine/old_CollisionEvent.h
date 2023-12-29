#pragma once
#include "bsepch.h"

class Contact;

class CollisionEvent : public Event {
public:
	CollisionEvent(Contact* contact) : contact(contact) {}

	std::string ToString() const override {
		std::stringstream ss;
		ss << "CollisionEvent: ";
		return ss.str();
	}

	EVENT_CLASS_TYPE(CollisionOccurred)
	EVENT_CLASS_CATEGORY(None)
private:
	Contact* contact;
};