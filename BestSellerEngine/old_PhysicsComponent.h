#pragma once
#include "bsepch.h"

	class PhysicsComponent {
	public:
		PhysicsComponent(float mass) : mass(mass), velocity(0.0f), dampingFactor(0.98f) {}
		
		void UpdatePhysics(float deltaTime) {
			UpdateVelocity(deltaTime);
			UpdatePosition(deltaTime);
		}

		void ApplyForce(const glm::vec3& force) {
			acceleration += force / mass;
		}

		void SetMass(float newMass) { mass = newMass; }
		float GetMass() const { return mass; }

		const glm::vec3& GetVelocity() const { return velocity; }
		void SetVelocity(const glm::vec3& newVelocity) { velocity = newVelocity; }

	private:
		float mass;
		glm::vec3 velocity;
		glm::vec3 acceleration;
		float dampingFactor; // Friction or air resistance. Should normally be a fraction less than 1.

		void UpdateVelocity(float deltaTime) {
			velocity += acceleration * deltaTime;
			velocity *= dampingFactor;
		}

		void UpdatePosition(float deltaTime) {
			//transform.Translate(velocity * deltaTime); // TODO: PhysicsComponent doesn't know about TransformComponent.
		}
	};