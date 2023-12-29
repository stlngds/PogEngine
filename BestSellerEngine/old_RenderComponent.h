#pragma once
#include "bsepch.h"

	class RenderComponent {
	public:
		RenderComponent(Mesh* mesh, Shader* shader, Texture* texture) : mesh(mesh), shader(shader), texture(texture) {}

		void Render() {

		}

	private:
		Mesh* mesh;
		Shader* shader;
		Texture* texture;
	};