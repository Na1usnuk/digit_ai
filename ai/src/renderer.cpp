#include "../include/renderer.hpp"


void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

renderer::renderer()
{
}

renderer::~renderer()
{
}

void renderer::clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void renderer::draw(const vertex_array& va, const index_buffer& ib, const shader& sh) const
{
	sh.bind();
	va.bind();
	ib.bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr));
}
