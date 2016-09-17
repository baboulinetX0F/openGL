#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragPath)
{
	// Read shaders files intro strings
	std::ifstream ifs = std::ifstream(vertexPath);
	std::string vertexCode((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	
	ifs = std::ifstream(fragPath);
	std::string fragCode((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	
	// Compile Shaders
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	GLuint fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragCode.c_str();

	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glShaderSource(fragShader, 1, &fShaderCode, NULL);

	GLint success;
	GLchar infoLog[512];

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	_program = glCreateProgram();
	glAttachShader(_program, vertexShader);
	glAttachShader(_program, fragShader);
	glLinkProgram(_program);

	glGetProgramiv(_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

void Shader::Use()
{
	glUseProgram(this->_program);
}
