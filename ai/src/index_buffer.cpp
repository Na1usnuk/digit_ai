#include "../include/index_buffer.hpp"
#include "../include/renderer.hpp"


index_buffer::index_buffer(const unsigned int* data, unsigned int count)
	: m_count(count)
{
	GLCall(glGenBuffers(1, &m_id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

index_buffer::~index_buffer()
{
	GLCall(glDeleteBuffers(1, &m_id));
}

void index_buffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void index_buffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

