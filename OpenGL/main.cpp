#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <fstream>

#include "Shader.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, 
	// closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, int argv)
{
	// Init glfw
	if (!glfwInit()) {
		std::cerr << "Couldn't initialize GLFW" << std::endl;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Learning", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW Window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Enable glewExperimental for modern techniques
	glewExperimental = GL_TRUE;
	
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init GLEW" << glewGetErrorString(glewInit()) << std::endl;
		return -1;
	}

	// Get the width and height from GLFW windows and give it to the viewport
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glfwSetKeyCallback(window, key_callback);
	
	Shader* def = new Shader("default.vert", "default.frag");

	// Test Rendering Data
	GLfloat vertices[] = {
		// First triangle
		-0.5f, -0.5f, 0.0f,  // Left 
		0.5f, -0.5f, 0.0f,  // Right
		0.0f, 0.5f, 0.0f,  // Top		
	};
	
	GLuint VBO;
	glGenBuffers(1, &VBO);	

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
			
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Change color uniform var over time
		GLfloat time = glfwGetTime();
		GLfloat color = (sin(time) / 2) + 0.5;
		GLuint colorUniformLocation = glGetUniformLocation(def->_program, "ourColor");
		def->Use();
		glUniform4f(colorUniformLocation, color, 0.0f, 0.0f, 1.0f);
				
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);	

		glfwSwapBuffers(window);
	}
		
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
	
	return 0;
}