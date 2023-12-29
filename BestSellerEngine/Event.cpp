#include "bsepch.h"

Event::Event() : UserData(nullptr)
{
}

Event::~Event()
{
}

void Event::SetUserData(void* data)
{
	UserData = data;
}

void* Event::GetUserData()
{
	return UserData;
}


EventManager* EventManager::instance = nullptr;

EventManager* EventManager::GetInstance()
{
	static EventManager* instance = new EventManager;
	return instance;
}

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::RegisterEvent(Event* event)
{
	events.push_back(event);
}

void EventManager::DispatchEvents(Node* scene)
{
	for (GameObject* go : static_cast<Root*>(scene)->GetRoots())
	{
		for (Event* pEvent : events)
			go->HandleEvent(pEvent);
	}

	for (Event* pEvent : events)
	{
		SceneChangeEvent* evt = dynamic_cast<SceneChangeEvent*>(pEvent);
		if (evt)
			GameEngine::GetInstance()->HandleEvent(evt);
	}
}

void EventManager::FlushEvents()
{
	for (Event* pEvent : events)
		delete pEvent;
	events.clear();
}
