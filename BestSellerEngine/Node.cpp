#include "bsepch.h"

Node::~Node()
{

}

void Node::AddChild(Node* node)
{
	node->parent = this;
	children.push_back(node);
}

std::string Node::GetName()
{
	return name;
}

void Node::SetName(std::string name)
{
	this->name = name;
}

bool Node::NeedsToBeDeleted()
{
	return toBeDeleted;
}

void Node::SetGeometry(Geometry* mesh)
{
	this->mesh = mesh;
}

Geometry* Node::GetGeometry()
{
	return mesh;
}

std::vector<Material*>* Node::GetMaterialsReference()
{
	return &materials;
}

std::vector<Node*>& Node::GetChildren()
{
	// TODO: insert return statement here
	return children;
}

Node* Node::GetParent() const
{
	return parent;
}

Transform& Node::GetTransform()
{
	return trans;
}

Transform& Node::GetWorldTransform()
{
	return worldT;

}

void Node::Update()
{
	// check if needs to inherit the transform from parent
	if (parent)
	{
		glm::mat4 localM = this->GetTransform().GetModelMatrix();
		glm::mat4 parentWorldM = parent->GetWorldTransform().GetModelMatrix();
		glm::mat4 thisWorldM = parentWorldM * localM;

		this->GetWorldTransform().Compose(thisWorldM);
	}
	else
	{
		this->worldT = this->trans;
	}


	// update the transform of every children node
	for (Node* node : children)
		node->Update();

}

void Node::Draw()
{
	for (Node* node : children)
		node->Draw();
}

void Node::Destroy() // New Function in the Node class
{
	for (size_t i = 0; i < children.size(); ++i)
	{
		children[i]->Destroy();
		delete children[i];
		children[i] = nullptr;
	}

	children.clear();

}