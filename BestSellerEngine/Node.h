#pragma once
#include "bsepch.h"
class Node
{
public:
	Node() : parent(nullptr), mesh(nullptr) {}
	virtual ~Node();

	void AddChild(Node* node);
	std::string GetName();
	void SetName(std::string name);
	bool NeedsToBeDeleted();
	void SetGeometry(Geometry* mesh);
	Geometry* GetGeometry();
	Transform& GetTransform();
	Transform& GetWorldTransform();
	std::vector<Material*>* GetMaterialsReference();
	std::vector<Node*>& GetChildren();
	Node* GetParent() const;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();


protected:

	std::string name;
	bool toBeDeleted;

	std::vector<Node*> children;
	Node* parent;

	Transform trans;
	Transform worldT;

	Geometry* mesh;
	std::vector<Material*> materials;
};