#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

int main(int argc, int argv)
{
	// Init glfw
	glfwInit();
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

	// Enable glewExperimental for modern techniques
	glewExperimental = GL_TRUE;
	if (!glewInit())
	{
		std::cout << "Failed to init GLEW\n";
		return -1;
	}

	// Get the width and height from GLFW windows and give it to the viewport
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	
	return 0;
}