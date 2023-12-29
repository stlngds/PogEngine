#pragma once

//#include <glew/glew.h>
//#include <iostream>
//#include "VertexArray.h"
//#include "IndexBuffer.h"
//#include "Shader.h"
#include "bsepch.h"
class VertexArray;
class IndexBuffer;
class Shader;

#define DEBUG

#ifdef DEBUG
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) {GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__)) }
#else
#define ASSERT(x) x;
#define GLCall(x) x;
#endif

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line); 

////////////////////////////////////////////////////

struct FrameBuffer {
    int Width = 0;
    int Height = 0;
};

class Renderer {
public:
    ~Renderer();
    static Renderer* GetInstance();

    // Setup APIs
    bool Start();
    void Stop();
    void SetOpenGLVersion(int major, int minor);
    void SetDebugMode();
    bool LoadOpenGLFunctions();
    void BufferUpdate();
    void SwapBuffers();
    FrameBuffer GetFrameBuffer();
    GLFWwindow* GetWindow();
    bool GenerateWindow(int width, int height, std::string title);
    bool IsWindowClosing();
    void RegisterInputCallback(void(*fn)(GLFWwindow* window, int key, int scancode, int action, int mods));
    void RegisterWindowSystemCallbacks();

    // Mesh modelling APIs
    void GenerateSceneBuffers(Geometry* geometry, int vertexCount);
    void InterpretBuffers(Geometry* geometry);
    Shader* BuildShader(std::string filepath);
    Shader* BuildShader(std::string vsfp, std::string fsfp);
    Texture* BuildTexture(std::string filepath);
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    //void Draw(const VertexArray& va, const Shader& shader) const; // No IBO.
    void Clear() const;

    void UpdateModelMatrix(Transform* transform, int shaderProgram, std::string matrixUniformName);

private:
    Renderer();

    static Renderer* instance;
    Shader* shaderHandle;
    GLFWwindow* pWindow;
    FrameBuffer frameBuffer;

    static void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height);
    static void GLFWErrorCallback(int error, const char* description);
    static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
        std::cout << "OpenGL Debug: " << message << std::endl;
    }
};