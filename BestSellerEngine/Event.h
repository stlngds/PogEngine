#pragma once


class Event {
public:
	Event();
	virtual ~Event();

	void SetUserData(void* data);
	void* GetUserData();

private:
	void* UserData;
};


class EventManager {
public:
	static EventManager* GetInstance();

	~EventManager();

	void RegisterEvent(Event* event);
	void DispatchEvents(Node* scene);
	void FlushEvents();

	std::vector<Event*> events; // TODO: reset to private

private:

	EventManager();
	static EventManager* instance;

	

};

class CollisionEvent : public Event
{
public:

	CollisionEvent() {}
	~CollisionEvent() {}

};