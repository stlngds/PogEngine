#pragma once
#include "bsepch.h"

enum PhysicsShapeType {
	CIRCLE,
	AABB_RECT,
	OBB_RECT,
	MAX_SHAPES
};

class Shape {
	public:
		Shape() {}
		Shape(PhysicsShapeType type) : type(type) {}

		virtual ~Shape() {}
		virtual void Update() = 0;
		virtual void Scale(glm::vec3 scale) = 0;

		PhysicsShapeType GetType() { return type; }
		void SetType(PhysicsShapeType type) { this->type = type; }

		Body* body;

	private:

	protected:
		PhysicsShapeType type;
};
