#include "bsepch.h"

WindowHandler* WindowHandler::instance = nullptr;

WindowHandler::WindowHandler() : glfwSuccess(false), pWindow(nullptr), pMonitor(nullptr), shouldClose(false)
{
	renderer = Renderer::GetInstance();
}

WindowHandler::~WindowHandler()
{
	delete renderer;
}

WindowHandler& WindowHandler::GetInstance()
{
	static WindowHandler instance;
	return instance;
}

/*
void WindowHandler::SwapBuffers()
{
	renderer->SwapBuffers();
}
*/

void WindowHandler::SwapBuffers()
{
	glfwSwapBuffers(pWindow);
}

GLFWwindow* WindowHandler::GetCurrentContext()
{
	return glfwGetCurrentContext();
}

glm::vec2 WindowHandler::GetWindowBufferDimensions()
{
	return glm::vec2(renderer->GetFrameBuffer().Width, renderer->GetFrameBuffer().Height);
}

/*
void WindowHandler::Init()
{
	// set default props if not initialized
	if (Props.Title.empty())
		Props.Title = "Untitled";

	if (Props.Height == 0)
		Props.Height = 480;

	if (Props.Width == 0)
		Props.Width = 640;

	// initialize glfw
	if (glfwSuccess)
	{
		std::cout << "GLFW is already initialized!";
		exit(EXIT_FAILURE);
	}


	if (!renderer->Start())
		exit(EXIT_FAILURE);
	glfwSuccess = true;

	// Initialize OpenGL Context
	renderer->SetOpenGLVersion(4, 3);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Create window
	bool windowCreated = renderer->GenerateWindow(Props.Width, Props.Height, Props.Title);
	if (!windowCreated)
		exit(EXIT_FAILURE);


	// Initialize glew (or other gl functions loader)
	if (!renderer->LoadOpenGLFunctions())
		exit(EXIT_FAILURE);


	//renderer->SetDebugMode();
	renderer->RegisterWindowSystemCallbacks();
	glfwSetKeyCallback(renderer->GetWindow(), this->GLFWWindowKeyCallback);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
}
*/

void WindowHandler::Init()
{
	// set default props if not initialized
	if (Props.Title.empty())
		Props.Title = "Untitled";

	if (Props.Height == 0)
		Props.Height = 480;

	if (Props.Width == 0)
		Props.Width = 640;

	// initialize glfw
	if (glfwSuccess)
	{
		std::cout << "GLFW is already initialized!";
		exit(EXIT_FAILURE);
	}

	glfwSetErrorCallback(this->GLFWErrorCallback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwSuccess = true;

	// Initialize OpenGL Context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Create window
	pWindow = glfwCreateWindow(Props.Width, Props.Height, Props.Title.c_str(), NULL, NULL);
	if (!pWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(pWindow);

	// Initialize glew (or other gl functions loader)
	GLenum glewError = glewInit();
	if (GLEW_OK != glewError)
	{
		std::cout << "Terminating program. Reason:" << std::endl;
		std::cout << "Error in GLEW: " << glewGetErrorString(glewError) << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwSetWindowSizeCallback(pWindow, this->GLFWWindowSizeCallback);
	glfwSetKeyCallback(pWindow, this->GLFWWindowKeyCallback);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
}

/*
void WindowHandler::Update()
{
	if (!renderer->GetWindow())
	{
		std::cout << "Window has not been initialized yet. Closing program..." << std::endl;
		exit(EXIT_FAILURE);
	}

	// this should not be responsibility of Window. Maybe something like a BufferDraw
	renderer->BufferUpdate();

	if (renderer->IsWindowClosing())
		shouldClose = true;
}
*/

void WindowHandler::Update()
{
	if (!pWindow)
	{
		std::cout << "Window has not been initialized yet. Closing program..." << std::endl;
		exit(EXIT_FAILURE);
	}

	// this should not be responsibility of Window. Maybe something like a BufferDraw
	glfwGetFramebufferSize(pWindow, &FrameBuffer.Width, &FrameBuffer.Height);
	glViewport(0, 0, FrameBuffer.Width, FrameBuffer.Height);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();

	if (glfwWindowShouldClose(pWindow))
		shouldClose = true;
}

void WindowHandler::ShutDown()
{
	if (!pWindow)
	{
		std::cout << "Window can't shutdown because it has not been initialized yet. Closing program..." << std::endl;
		exit(EXIT_FAILURE);
	}
	if(!glfwSuccess)
	{
		std::cout << "GLFW can't shutdown because it has not been initialized yet. Closing program..." << std::endl;
		exit(EXIT_FAILURE);
	}

	renderer->Stop();
}

bool WindowHandler::ShouldClose()
{
	return shouldClose;
}


void WindowHandler::GLFWErrorCallback(int error, const char* description)
{
	std::cout << "Error in GLFW: " << description << std::endl;
}

void WindowHandler::GLFWWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	std::cout << "Window being resized... ";
	std::cout << "Width: " << width << " | Height: " << height << std::endl;
}

void WindowHandler::GLFWWindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
