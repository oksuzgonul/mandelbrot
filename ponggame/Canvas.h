#pragma once
#include <vector>
#include <cstring>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shaderloader.hpp"

class Canvas
{
public:
	Canvas();
	Canvas(
		glm::vec2 top_left,
		glm::vec2 top_right,
		glm::vec2 bottom_right,
		glm::vec2 bottom_left, 
		glm::mat4* ProjectionW, 
		glm::mat4* ViewW);
	void drawCanvas(glm::vec4 Position);
	void CleanUp();
private:
	unsigned int CanvasVertexBufferID;
	unsigned int CanvasShaderID;
	unsigned int CanvasVertexArrayID;
	unsigned int MatrixID;
	unsigned int ControlsID;
	//unsigned int CanvasUVBufferID;
	//unsigned int CanvasTextureID;
	//unsigned int CanvasUniformID;
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> uvs;
	glm::mat4* Projection;
	glm::mat4* View;
	void generateRectangularVertices(
		glm::vec2 top_left,
		glm::vec2 top_right,
		glm::vec2 bottom_right,
		glm::vec2 bottom_left);
};