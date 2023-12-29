#include "bsepch.h"

Body::Body()
{
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(0.0f, 0.0f, 0.0f);

	Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	Acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	Force = glm::vec3(0.0f, 0.0f, 0.0f);
	AngularVelocity = glm::vec3(0.0f, 0.0f, 0.0f);

	float Mass = 0.0f;
	float InverseMass = 0.0f;
}

Body::~Body() {

}

void Body::Init() {

}

void Body::Update() {
	if (!bodyShape) return;

	bodyShape->Scale(this->Scale);

	if (this->bodyShape->GetType() == OBB_RECT) {
		static_cast<OBB*>(bodyShape)->Direction(this->Rotation);
		static_cast<OBB*>(bodyShape)->Position(this->Position);
	}

	bodyShape->Update();
}

void Body::Integrate() {

}

void Body::SetShape(Shape* shape) {
	bodyShape = shape;
}

Shape* Body::GetShape() {
	return bodyShape;
}