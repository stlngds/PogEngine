#pragma once
#include "bsepch.h"

class GameObject : public Node
{
public:
	GameObject();
	virtual ~GameObject();

	void Initialize();
	void HandleEvent(Event* evt);
	void Serialize() {}
	void Deserialize(const rapidjson::Value& obj);

	bool IsAlive();
	bool MarkAsDelete();
	void SetAlive(bool state);
	void SetDelete(bool state);

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	template <class T>
	T* FindComponent()
	{
		std::vector<Component*>::iterator it = components.begin();
		while (it != components.end())
		{
			T* type = dynamic_cast<T*>(*it);
			if (type != 0)
				return type;
			it = it + 1;
		}
		return nullptr;
	}

	template <class T>
	T* AddComponent()
	{
		T* component = new T;
		component->SetOwner(this);
		components.push_back(component);
		return component;
	}

private:
	std::vector<Component*> components;
	bool isAlive;

	void Shutdown();
};

class GameObjectSystemComponentConstants
{
public:
	static const char* const PHYSICS_COMPONENT;
	static const char* const POSITION;
	static const char* const ROTATION;
	static const char* const SCALE;
	static const char* const VELOCITY;
	static const char* const ACCELERATION;
	static const char* const FORCE;
	static const char* const ANG_VELO;
	static const char* const MASS;
	static const char* const INV_MASS;
	static const char* const SHAPE_TYPE;

	static const char* const RENDER_COMPONENT;
	static const char* const TEXTURE_COORDS;
	static const char* const INDICES;
	static const char* const COLORS;
	static const char* const COLOR1;
	static const char* const COLOR2;
	static const char* const COLOR3;
	static const char* const VERTICES;
	static const char* const V1;
	static const char* const V2;
	static const char* const V3;
	static const char* const MESH_TYPE;
	static const char* const TRIANGLE_MESH;
	static const char* const POINT_CLOUD;
	static const char* const QUAD_MESH;
	static const char* const SHADER;
	static const char* const VERTEX_FILE;
	static const char* const FRAGMENT_FILE;
	static const char* const ATTRIBUTES; // since it's a dynamic array in code, we don't need to know the names of each.
	static const char* const TEXTURE_PATH;

	static const char* const TRANSFORM_COMPONENT;
	static const char* const POSITION_TRANS;
	static const char* const ROTATION_TRANS;
	static const char* const SCALE_TRANS;

};