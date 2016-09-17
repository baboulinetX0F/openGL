#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>

#include <GL\glew.h>

class Shader
{
public:
	GLuint _program;	// Id of the shader program
	Shader(const GLchar* vertexPath, const GLchar* fragPath);	// Constructor
	void Use();
};

#endif

