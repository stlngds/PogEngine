//#include "IndexBuffer.h"
//#include "Renderer.h"
#include "bsepch.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_Count(count) {
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_RendererID)); // Assigns a unique integer value to vertexBuffer.
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); // The object of ID {vertexBuffer} is an array buffer. Future draw calls will use the data in the currently-bound buffer to determine what they draw on the screen. (i.e., glDrawArrays()). In photoshop terms, it's kinda like selecting a layer.
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW)); // Feed the buffer our vertex data. We don't modify vertices[] so we declare GL_STATIC_DRAW instead of DYNAMIC. That declaration is just a hint - you *can* modify vertices[] with GL_STATIC_DRAW, but things might go slower than they would otherwise.
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}