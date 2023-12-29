//#include "VertexBuffer.h"
//#include "Renderer.h"
#include "bsepch.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    GLCall(glGenBuffers(1, &m_RendererID)); // Assigns a unique integer value to vertexBuffer.
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // The object of ID {vertexBuffer} is an array buffer. Future draw calls will use the data in the currently-bound buffer to determine what they draw on the screen. (i.e., glDrawArrays()). In photoshop terms, it's kinda like selecting a layer.
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); // Feed the buffer our vertex data. We don't modify vertices[] so we declare GL_STATIC_DRAW instead of DYNAMIC. That declaration is just a hint - you *can* modify vertices[] with GL_STATIC_DRAW, but things might go slower than they would otherwise.
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}