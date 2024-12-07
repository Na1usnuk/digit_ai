#include "../include/shader.hpp"
#include "../include/renderer.hpp"

#include <sstream>
#include <fstream>

struct shaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

shader::shader(const std::string& filepath)
    : m_id(0), m_filepath(filepath)
{
	shaderProgramSource src = parseShader(filepath);
	m_id = createProgram(src.vertexSource, src.fragmentSource);
}

shader::~shader()
{
	GLCall(glDeleteProgram(m_id));
}

void shader::bind() const
{
	GLCall(glUseProgram(m_id));
}

void shader::unbind() const
{
	GLCall(glUseProgram(0));
}

void shader::setUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
	GLCall(glUniform4f(getUniformLocation(name), f0, f1, f2, f3));
}

int shader::getUniformLocation(const std::string& name)
{
	GLCall(int location = glGetUniformLocation(m_id, name.c_str()));
	if (location == -1)
		std::cerr << "[WARNING]Uniform '" << name << "' doesn`t exist!" << std::endl;
	return location;
}

unsigned int shader::compileShader(unsigned int type, const std::string& source)
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int l;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &l));
		char* msg = (char*)alloca(l * sizeof(char));
		GLCall(glGetShaderInfoLog(id, l, &l, msg));
		std::cerr << "[ERROR]Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader. " << msg << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}
	return id;
}

unsigned int shader::createProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLCall(unsigned int prog = glCreateProgram());
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(prog, vs));
	GLCall(glAttachShader(prog, fs));
	GLCall(glLinkProgram(prog));
	GLCall(glValidateProgram(prog));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return prog;
}

shaderProgramSource shader::parseShader(const std::string& filepath)

{
	std::ifstream stream(filepath);

	enum class shaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	shaderType type = shaderType::NONE;
	std::stringstream ss[2];
	std::string line;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = shaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = shaderType::FRAGMENT;
		}
		else
			ss[(int)type] << line << '\n';
	}
	return { ss[0].str(), ss[1].str() };
}
