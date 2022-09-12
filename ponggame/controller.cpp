#pragma once
#include <iostream>
#include <cmath>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
extern GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm; 

#include "controller.hpp"

float mousePos;
float deltaTime;
glm::vec2 movementDir;

float getMouse()
{
	return mousePos;
}

float getDeltaTime()
{
	return deltaTime;
}

glm::vec4 getCenter()
{
	updatePosition();
	glm::vec4 center(0);
	center.x = movementDir.x;
	center.y = movementDir.y;
	return center;
}

void updatePosition()
{
	static double lastTime = glfwGetTime();
	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);

	movementDir = glm::vec2(0);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		movementDir.y = 2 * deltaTime;
	}
		
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		movementDir.y = -2 * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		movementDir.x = -2 * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		movementDir.x = 2 * deltaTime;
	}

	lastTime = currentTime;
}