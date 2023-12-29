//#include "Renderer.h"
#include "bsepch.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

////////////////////////////////////////////////////

Renderer* Renderer::instance = nullptr;

Renderer::Renderer() {

}

Renderer::~Renderer() {
	pWindow = nullptr;
	delete instance;
}

Renderer* Renderer::GetInstance() {
    static Renderer* instance = new Renderer();
    return instance;
}

bool Renderer::Start()
{
	glfwSetErrorCallback(this->GLFWErrorCallback);
    if (!glfwInit())
        return false;
    return true;
}

void Renderer::Stop()
{
    glfwDestroyWindow(pWindow);
    glfwTerminate();
}

void Renderer::SetOpenGLVersion(int major, int minor)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

void Renderer::SetDebugMode()
{
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
}

bool Renderer::LoadOpenGLFunctions()
{
	GLenum glewError = glewInit();
	if (GLEW_OK != glewError)
	{
		std::cout << "Error in GLEW: " << glewGetErrorString(glewError) << std::endl;
		return false;
	}
	return true;
}

void Renderer::BufferUpdate()
{
	glfwGetFramebufferSize(pWindow, &frameBuffer.Width, &frameBuffer.Height);
	glViewport(0, 0, frameBuffer.Width, frameBuffer.Height);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SwapBuffers()
{
	glfwSwapBuffers(pWindow);
}

FrameBuffer Renderer::GetFrameBuffer()
{
	return frameBuffer;
}

bool Renderer::GenerateWindow(int width, int height, std::string title)
{
	pWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!pWindow)
	{
		glfwTerminate();
		std::cout << "Problem creating window" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(pWindow);
	return true;
}

bool Renderer::IsWindowClosing()
{
	if (glfwWindowShouldClose(pWindow))
		return true;
	return false;
}

GLFWwindow* Renderer::GetWindow()
{
	return pWindow;
}

void Renderer::RegisterInputCallback(void(*fn)(GLFWwindow* window, int key, int scancode, int action, int mods))
{
	glfwSetKeyCallback(pWindow, fn);
}

void Renderer::RegisterWindowSystemCallbacks()
{
	glfwSetWindowSizeCallback(pWindow, this->GLFWWindowSizeCallback);
}

void Renderer::GLFWWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	std::cout << "Window being resized... ";
	std::cout << "Width: " << width << " | Height: " << height << std::endl;
}



void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

/*
void Renderer::Draw(const VertexArray& va, const Shader& shader) const
{
	va.Bind();
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}
*/

void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::UpdateModelMatrix(Transform* transform, int shaderProgram, std::string matrixUniformName)
{
	GLint modelMatrixLocation;
	modelMatrixLocation = glGetUniformLocation(shaderProgram, matrixUniformName.c_str());
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &transform->GetModelMatrix()[0][0]);
}

Texture* Renderer::BuildTexture(std::string filepath)
{
    Texture* tempt = new Texture(filepath);
    return tempt;
}

Shader* Renderer::BuildShader(std::string filepath)
{
    Shader* temps = new Shader(filepath);
    return temps;
}

Shader* Renderer::BuildShader(std::string vsfp, std::string fsfp) {
	Shader* temps = new Shader(vsfp, fsfp);
	return temps;
}

void Renderer::GenerateSceneBuffers(Geometry* geometry, int vertexCount)
{
    geometry->VAO->Bind();
    geometry->VBO->Bind();
}

void Renderer::InterpretBuffers(Geometry* geometry)
{
    geometry->VAO->AddBuffer(*geometry->VBO, *geometry->VBL);
}

void Renderer::GLFWErrorCallback(int error, const char* description)
{
	std::cout << "Error in GLFW: " << description << std::endl;
}
