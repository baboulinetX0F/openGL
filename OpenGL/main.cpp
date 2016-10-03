#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"

Camera* _cam;
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

// test variables
glm::vec3 mdlPos = glm::vec3(0.0f, 1.0f, 0.0f);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, 
	// closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_W)
		_cam->processKeyboard(CameraDirection::FORWARD);
	if (key == GLFW_KEY_S)
		_cam->processKeyboard(CameraDirection::BACKWARD);
	if (key == GLFW_KEY_D)
		_cam->processKeyboard(CameraDirection::RIGHT);
	if (key == GLFW_KEY_A)
		_cam->processKeyboard(CameraDirection::LEFT);

	// Test move command lamp
	if (key == GLFW_KEY_RIGHT)
		mdlPos += glm::vec3(0.1f, 0.0f, 0.0f);
	if (key == GLFW_KEY_LEFT)
		mdlPos -= glm::vec3(0.1f, 0.0f, 0.0f);
	if (key == GLFW_KEY_UP)
		mdlPos += glm::vec3(0.0f, 0.1f, 0.0f);
	if (key == GLFW_KEY_DOWN)
		mdlPos -= glm::vec3(0.0f, 0.1f, 0.0f);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	GLfloat x_offset = xpos - lastX;
	GLfloat y_offset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	_cam->processMouse(x_offset, y_offset);
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

	GLFWwindow* window = glfwCreateWindow(800, 600, "openGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW Window\n";
		glfwTerminate();
		return -1;
	}

	// Assign Context of window (only for AMD cards)
	glfwMakeContextCurrent(window);

	// Enable glewExperimental for modern techniques
	glewExperimental = GL_TRUE;

	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	glfwSetCursorPosCallback(window, mouse_callback);

	// data pattern : [(vec3) vertex | (vec2) texCoord | (vec3) normalVector]
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f
	};
	
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f, 0.2f, 2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f, 2.0f, -12.0f),
		glm::vec3(0.0f, 0.0f, -3.0f)
	};


	GLuint VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);

	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);	

	_cam = new Camera();

	Shader* lampShader = new Shader("shaders/lamp.vert", "shaders/lamp.frag");
	Shader mdlShad = Shader("shaders/model_shaders/default.vert", "shaders/model_shaders/mdlLight.frag");	
		

	Model nanosuit = Model("models/nanosuit/nanosuit.obj");
	
	// Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0){ // If last prinf() was more than 1 sec ago
			// printf and reset timer
			double frameTime = 1000.0 / double(nbFrames);
			glfwSetWindowTitle(window, ("openGL Frame time : " + std::to_string(frameTime) + " FPS : " + std::to_string(1000/frameTime)).c_str());
			nbFrames = 0;
			lastTime += 1.0;
		}
		
		glfwPollEvents();
				
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

		glm::mat4 view, projection, model;		

		view = _cam->getViewMatrix();
		projection = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
		
		lampShader->Use();		

		GLuint modelLoc = glGetUniformLocation(lampShader->_program, "model");
		GLuint viewLoc = glGetUniformLocation(lampShader->_program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		GLuint projLoc = glGetUniformLocation(lampShader->_program, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(lightVAO);
		for (int i = 0; i < 4; i++)
		{
			model = glm::mat4();
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		// model drawing
		
		mdlShad.Use();			

		modelLoc = glGetUniformLocation(mdlShad._program, "model");

		viewLoc = glGetUniformLocation(mdlShad._program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		projLoc = glGetUniformLocation(mdlShad._program, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glUniform3f(glGetUniformLocation(mdlShad._program, "viewPos"), _cam->_pos.x, _cam->_pos.y, _cam->_pos.z);

		glUniform3f(glGetUniformLocation(mdlShad._program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(mdlShad._program, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(mdlShad._program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(mdlShad._program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);

		for (int i = 0; i < 4; i++)
		{
			std::ostringstream oss;
			oss << "pointLights[" << i << "].";
			std::string tmp = oss.str();
			glUniform3f(glGetUniformLocation(mdlShad._program, (tmp + std::string("position")).c_str()), pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);			
			glUniform3f(glGetUniformLocation(mdlShad._program, (tmp + std::string("ambient")).c_str()), 0.05f, 0.05f, 0.05f);
			glUniform3f(glGetUniformLocation(mdlShad._program, (tmp + std::string("diffuse")).c_str()), 0.8f, 0.8f, 0.8f);
			glUniform3f(glGetUniformLocation(mdlShad._program, (tmp + std::string("specular")).c_str()), 1.0f, 1.0f, 1.0f);
			glUniform1f(glGetUniformLocation(mdlShad._program, (tmp + std::string("constant")).c_str()), 1.0f);
			glUniform1f(glGetUniformLocation(mdlShad._program, (tmp + std::string("linear")).c_str()), 0.09);
			glUniform1f(glGetUniformLocation(mdlShad._program, (tmp + std::string("quadratic")).c_str()), 0.032);
		}
		
		model = glm::mat4();
		model = glm::translate(model, mdlPos);
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		nanosuit.Draw(mdlShad);

		glfwSwapBuffers(window);
	}

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glfwTerminate();

	return 0;
}