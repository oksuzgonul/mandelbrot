// Standard headers
#define GLEW_STATIC
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW to import extensions
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "shaderloader.hpp"
#include "controller.hpp"
#include "Canvas.h"

#ifndef NDEBUG
void APIENTRY DebugOutputCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {

	printf("OpenGL Debug Output message : ");

	if (source == GL_DEBUG_SOURCE_API_ARB)					printf("Source : API; ");
	else if (source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)	printf("Source : WINDOW_SYSTEM; ");
	else if (source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)	printf("Source : SHADER_COMPILER; ");
	else if (source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)		printf("Source : THIRD_PARTY; ");
	else if (source == GL_DEBUG_SOURCE_APPLICATION_ARB)		printf("Source : APPLICATION; ");
	else if (source == GL_DEBUG_SOURCE_OTHER_ARB)			printf("Source : OTHER; ");

	if (type == GL_DEBUG_TYPE_ERROR_ARB)						printf("Type : ERROR; ");
	else if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)	printf("Type : DEPRECATED_BEHAVIOR; ");
	else if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)	printf("Type : UNDEFINED_BEHAVIOR; ");
	else if (type == GL_DEBUG_TYPE_PORTABILITY_ARB)			printf("Type : PORTABILITY; ");
	else if (type == GL_DEBUG_TYPE_PERFORMANCE_ARB)			printf("Type : PERFORMANCE; ");
	else if (type == GL_DEBUG_TYPE_OTHER_ARB)				printf("Type : OTHER; ");

	if (severity == GL_DEBUG_SEVERITY_HIGH_ARB)				printf("Severity : HIGH; ");
	else if (severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)		printf("Severity : MEDIUM; ");
	else if (severity == GL_DEBUG_SEVERITY_LOW_ARB)			printf("Severity : LOW; ");

	printf("Message : %s\n", message);
};
#endif

int main()
{
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW failed to initialize.\n");
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifndef NDEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
#endif

	int height = 800;
	int width = 800;

	window = glfwCreateWindow(height, width, "mandelbrot", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open window.");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

#ifndef NDEBUG
	if (GLEW_ARB_debug_output) {
		printf("The OpenGL debugger available.\n");
		glDebugMessageCallbackARB(&DebugOutputCallback, NULL);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	}
	else {
		printf("ARB_debug_output unavailable.\n");
	}
#endif

	// Setting input mode
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwPollEvents();
	glfwSetCursorPos(window, height / 2, width / 2);

	printf("%s", glGetString(GL_VERSION));

	//set the view and projection matrices (set it once for all objects since it is a fixed camera)
	// 2D orthogonal projection matrix
	glm:: mat4 Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	// Fixed camera matrix
	glm:: mat4 View = glm::lookAt(
		glm::vec3(0, 0, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0) 
	);

	Canvas canvas = Canvas(
		glm::vec2(-1.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, -1.0f),
		glm::vec2(-1.0f, -1.0f),
		&Projection,
		&View);

	glm::vec4 SmoothPosition(0);
	glm::vec4 Position(0);

	do
	{
		glClear(GL_COLOR_BUFFER_BIT);

		Position += getCenter();
		SmoothPosition.x = std::lerp(SmoothPosition.x, Position.x, 0.003f);
		SmoothPosition.y = std::lerp(SmoothPosition.y, Position.y, 0.003f);
		SmoothPosition.z = get_zoom();
		canvas.drawCanvas(SmoothPosition);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	canvas.CleanUp();

	glfwTerminate();

	return 0;
}