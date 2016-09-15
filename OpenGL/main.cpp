#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

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

	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
			
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	
	return 0;
}