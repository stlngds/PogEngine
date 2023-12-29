#pragma once
#include "bsepch.h"
class GameObject;
class Event;
class Component
{
public:
	Component() : owner(nullptr) {}
	virtual ~Component() {}

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;
	virtual void HandleEvent(Event* evt) = 0;
	virtual void Deserialize(const rapidjson::Value& obj) = 0;

	GameObject* GetOwner() const { return owner; }
	void SetOwner(GameObject* gameobject) { owner = gameobject; }




protected:
	GameObject* owner;

};

class ComponentConstants
{
public:
	virtual const std::vector<const char*> GetComponentConstant() = 0;
};