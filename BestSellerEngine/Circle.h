#pragma once
#include "bsepch.h"

class Circle : public Shape {
public:
	Circle();
	~Circle();

	float Center, Radius;

	void Update();
	void Scale(glm::vec3 scale);

private:
	glm::vec3 scale;
};