#pragma once
#include "bsepch.h"

class OBB : public Shape {
public:
	OBB() {}
	~OBB() {}

	glm::vec4 TopRight, TopLeft, BottomLeft, BottomRight;

	void Update();
	void Scale(glm::vec3 scale);
	void Position(glm::vec3 center);
	void Direction(glm::vec3 eulerAngles);
	
	void GenerateNormals();
	glm::vec3 GetAxis1();
	glm::vec3 GetAxis2();

private:
	glm::vec3 scale;
	glm::vec4 center;
	glm::mat4 direction;

	std::array<glm::vec3, 2> separatingAxes;

	void generateProjections();
};