#include "../include/vertex_buffer.hpp"
#include "../include/renderer.hpp"

vertex_buffer::vertex_buffer(const void* data, unsigned int size)
	: m_id(0)
{
	GLCall(glGenBuffers(1, &m_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

vertex_buffer::~vertex_buffer()
{
	GLCall(glDeleteBuffers(1, &m_id));
}

void vertex_buffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

void vertex_buffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
