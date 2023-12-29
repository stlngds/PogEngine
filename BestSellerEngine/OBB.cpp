#include "bsepch.h"

void OBB::Update() {
	TopRight = center + direction * glm::vec4(scale.x, scale.y, 0.0f, 1.0f);
	TopLeft = center + direction * glm::vec4(-scale.x, scale.y, 0.0f, 1.0f);
	BottomLeft = center + direction * glm::vec4(-scale.x, -scale.y, 0.0f, 1.0f);
	BottomRight = center + direction * glm::vec4(scale.x, -scale.y, 0.0f, 1.0f);
}

void OBB::Scale(glm::vec3 scale) {
	this->scale = scale;
}

void OBB::Position(glm::vec3 center) {
	this->center = glm::vec4(center, 1.0f);
}

void OBB::Direction(glm::vec3 eulerAngles) {
	this->direction = glm::eulerAngleXYZ(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

void OBB::GenerateNormals() {
	glm::vec3 v;

	v = (TopRight - TopLeft);
	glm::vec3 normal1 = glm::vec3(-v.y, v.x, 0.0f);

	v = (TopLeft - BottomLeft);
	glm::vec3 normal2 = glm::vec3(-v.y, v.x, 0.0f);

	separatingAxes[0] = normal1;
	separatingAxes[1] = normal2;
}

glm::vec3 OBB::GetAxis1() {
	return separatingAxes[0];
}

glm::vec3 OBB::GetAxis2() {
	return separatingAxes[1];
}

void OBB::generateProjections() {
	return;
}