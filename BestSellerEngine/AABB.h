#pragma once
#include "bsepch.h"

class AABB : public Shape {
public:
	AABB();
	~AABB();

	float Left, Right, Top, Bottom;
	void Update();
	void Scale(glm::vec3 scale);
private:
	glm::vec3 scale;
};