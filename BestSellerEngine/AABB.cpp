#include "bsepch.h"

AABB::AABB() : Left(0.0f), Right(0.0f), Top(0.0f), Bottom(0.0f), Shape(AABB_RECT) {}

AABB::~AABB() {}

void AABB::Update() {
	Left = -scale.x;
	Right = scale.x;
	Top = scale.y;
	Bottom = -scale.y;
}

void AABB::Scale(glm::vec3 scale) {
	this->scale = scale;
}