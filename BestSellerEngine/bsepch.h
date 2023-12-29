#pragma once

#define GLFW_INCLUDE_NONE
// Libraries
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
//#include "imgui_impl_opengl3.h"

#include <glfw/glfw3.h>
#include <glew/glew.h>

#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <array>
#include <algorithm>
#include <stack>

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/matrix_decompose.hpp"

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

//#include "imgui-1.60/imgui.h"
//#include "imgui-1.60/examples/opengl3_example/imgui_impl_glfw_gl3.h"



// Core
#include "FramerateController.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

// Render
#include "Geometry.h"
#include "TriangleMesh.h"
#include "Transform.h"
#include "Material.h"
#include "Node.h"
#include "Color.h"
#include "Texture.h"
#include "Shader.h"
#include "Renderer.h"
#include "BSEWindow.h"
//#include "RectangleMesh.h"
//#include "PrimRectangle.h"
//#include "LineMesh.h"
//#include "PrimLine.h"

// Input
#include "Input.h"
//#include "InputKeys.h"
//#include "InputManager.h"

// Physics
#include "Body.h"
#include "Shape.h"
#include "AABB.h"
#include "OBB.h"
#include "Circle.h"
#include "CollisionGenerator.h"
#include "PhysicsManager.h"
#include "CollisionFunctions.h"

// Events
#include "Event.h"

// GameObject
#include "Component.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
//  Level Management
#include "Root.h"
#include "Scene.h"
#include "GameEngine.h"
#include "Game.h"

// Application Layer
//#include "ATriangleMesh.h"
//#include "ATriangleObject.h"
//#include "DebugQuad.h"

// User-defined
#include "SceneConstants.h"
#include "MainScene.h"

extern glm::mat4 projection;