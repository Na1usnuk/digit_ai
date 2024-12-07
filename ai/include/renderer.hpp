#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vertex_buffer.hpp"
#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer_layout.hpp"
#include "shader.hpp"

#include <cassert>
#include <iostream>

#define ASSERT(x) if(!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class renderer
{
public:

	renderer();
	~renderer();

	void clear() const;
	void draw(const vertex_array&, const index_buffer&, const shader&) const;

private:


};