#pragma once
#include "bsepch.h"

	class PogInput {
	public:


		static bool IsKeyPressed(int key) {
			return glfwGetKey(windowInstance, key) == GLFW_PRESS;
		}

		static bool IsMouseButtonPressed(int button) {
			return glfwGetMouseButton(windowInstance, static_cast<int32_t>(button)) == GLFW_PRESS;
		}

		static glm::vec2 GetMousePosition() {
			double xpos, ypos;
			GLCall(glfwGetCursorPos(windowInstance, &xpos, &ypos));
			return { (float)xpos, (float)ypos };
		}
		static float GetMouseX() {
			return GetMousePosition().x;
		}
		static float GetMouseY() {
			return GetMousePosition().y;
		}

	private:
		static GLFWwindow* windowInstance; // needs to be initialized?
	};
