#pragma once

#include "GL/glew.h"
#include "renderer.hpp"

#include <vector>

struct vertex_buffer_element
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}

		//ASSERT(false);

		return 0;
	}
};

class vertex_buffer_layout
{

public:

	vertex_buffer_layout() : m_stride(0) { }

	inline unsigned int stride() const { return m_stride; }
	inline const std::vector<vertex_buffer_element>& elements() const { return m_elements; }

	template<typename T>
	void push(unsigned int count)
	{
		//static_assert(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += count * vertex_buffer_element::getSizeOfType(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += count * vertex_buffer_element::getSizeOfType(GL_UNSIGNED_INT);
	}
	
	template<>
	void push<unsigned char>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += count * vertex_buffer_element::getSizeOfType(GL_UNSIGNED_BYTE);
	}

private:

	std::vector<vertex_buffer_element> m_elements;
	unsigned int m_stride;
};