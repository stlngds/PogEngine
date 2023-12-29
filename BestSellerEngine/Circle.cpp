#include "bsepch.h"

Circle::Circle() : Center(0.0f), Radius(0.0f), Shape(CIRCLE) {}

Circle::~Circle() {}

void Circle::Update() {
	// Update variables based on scale.
}

void Circle::Scale(glm::vec3 scale) {
	this->scale = scale;
}