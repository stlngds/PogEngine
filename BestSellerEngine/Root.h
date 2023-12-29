#pragma once
#include "bsepch.h"
class Root : public Node
{
public:

	void SetPosition(glm::vec3 pos) { trans.SetTranslate(pos); }
	glm::vec3 GetPosition() { trans.GetPosition(); }
	Body* GetPhysicsBody() { return physicalBody; }
	void LoadPhysics();
	void UpdatePhysics();
	std::vector<GameObject*> GetRoots();

	void Draw() { for (Node* node : children) node->Draw(); }

private:
	Body* physicalBody; // for physics support


};