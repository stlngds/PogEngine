#pragma once
#include "bsepch.h"

	class Mesh {
	public:
		Mesh(std::vector<float> vertices, std::vector<unsigned int> indices) : vertices(vertices), indices(indices) {
			InitMesh();
		}

		void Draw() {
			GLCall(glBindVertexArray(VAO));
			GLCall(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0));
			GLCall(glBindVertexArray(0));
		}

	private:
		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		unsigned int VAO, VBO, EBO;

		void InitMesh() {
			GLCall(glGenVertexArrays(1, &VAO));
		}
	};