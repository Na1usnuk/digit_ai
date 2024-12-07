#include "../include/renderer.hpp"
#include "../include/vertex_array.hpp"



vertex_array::vertex_array()
{
	GLCall(glGenVertexArrays(1, &m_id));
}

vertex_array::~vertex_array()
{
	GLCall(glDeleteVertexArrays(1, &m_id));
}

void vertex_array::add_buffer(const vertex_buffer& vb, const vertex_buffer_layout& layout)
{
	bind();
	vb.bind();

	const auto& elements = layout.elements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.stride(), (const void*)offset));
		offset += element.count * vertex_buffer_element::getSizeOfType(element.type);
	}

	
}

void vertex_array::bind() const
{
	GLCall(glBindVertexArray(m_id));
}

void vertex_array::unbind() const
{
	GLCall(glBindVertexArray(0));
}
