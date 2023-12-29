#pragma once
#include "bsepch.h"

	class Transform {
	public:
		Transform() : translate(glm::mat4(1.0f)), rotation(glm::mat4(1.0f)), scale(glm::mat4(1.0f)) {}

		void SetTranslate(const glm::vec3& newTranslate) { translate = glm::translate(glm::mat4(1.0f), newTranslate); }
		void SetRotation(const glm::vec3& newRotation) { rotation = glm::eulerAngleXYZ(newRotation.x, newRotation.y, newRotation.z); }
		void SetScale(const glm::vec3& newScale) { scale = glm::scale(glm::mat4(1.0f), newScale); }
		void SetScale(const float newScale) { scale = glm::scale(glm::mat4(1.0f), glm::vec3(newScale, newScale, newScale)); }
		void ResetModelMatrix() { model = glm::mat4(1.0f); }
		void Compose(glm::mat4 matrix) { model = matrix * translate * rotation * scale; }


		const glm::mat4& GetTranslate() const { return translate; }
		const glm::mat4& GetRotation() const { return rotation; }
		const glm::mat4& GetScale() const { return scale; }
		const glm::mat4& GetModelMatrix() const { return model; }
		const glm::vec3 GetPosition() const { return glm::vec3(translate[3][0], translate[3][1], translate[3][2]); }
		const glm::vec3 GetScaleVector() const { glm::vec3 scale, translation, skew; glm::vec4 perspective; glm::quat rotation; glm::decompose(model, scale, rotation, translation, skew, perspective); return scale; }
		const glm::vec3 GetRotationEulerAngles() const { glm::vec3 euler; glm::extractEulerAngleXYZ(GetRotation(), euler.x, euler.y, euler.z); return euler; }

	private:
		glm::mat4 translate, rotation, scale, model;
	};
