#pragma once
#include "bsepch.h"
class TransformComponent : public Component
{
public:
	TransformComponent();
	~TransformComponent();

	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 eulerAngles);
	void SetScale(glm::vec3 nonUniformScale);
	void SetScale(float uniformScale);

	glm::vec3 GetPosition() const;
	glm::vec3 GetOrientation() const;
	glm::vec3 GetScale() const;

	glm::mat4 GetTranslationMatrix() const;
	glm::mat4 GetRotationMatrix() const;
	glm::mat4 GetScaleMatrix() const;
	glm::mat4 GetModelMatrix() const;

	void Initialize();
	void Update();
	void Shutdown();
	void HandleEvent(Event* evt);
	void Serialize() {}
	void Deserialize(const rapidjson::Value& obj);
};