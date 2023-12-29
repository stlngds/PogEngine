#pragma once
#include "bsepch.h"

class Shape;

class Body {
	public:
		Body();
		~Body();

		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;

		glm::vec3 Velocity;
		glm::vec3 Acceleration;
		glm::vec3 Force;
		glm::vec3 AngularVelocity;

		float Mass, InverseMass;

		void Init();
		void Update();
		void Integrate();

		void SetShape(Shape* shape);
		Shape* GetShape();

	private:
		Shape* bodyShape;
};