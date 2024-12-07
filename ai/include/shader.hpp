#pragma once

#include <string>

struct shaderProgramSource;

class shader
{
public:

	shader(const std::string&);
	~shader();

	void bind() const;
	void unbind() const;

	void setUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

private:

	int getUniformLocation(const std::string&);
	unsigned int compileShader(unsigned int, const std::string&);
	shaderProgramSource parseShader(const std::string&);
	unsigned int createProgram(const std::string&, const std::string&);

private:

	unsigned int m_id;
	std::string m_filepath;
};

