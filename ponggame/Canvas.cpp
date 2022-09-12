#include "Canvas.h"

Canvas::Canvas()
{
}

Canvas::Canvas(
	glm::vec2 top_left,
	glm::vec2 top_right,
	glm::vec2 bottom_right,
	glm::vec2 bottom_left,
	glm::mat4* ProjectionW, 
	glm::mat4* ViewW) :
	Projection(ProjectionW),
	View(ViewW)
{
	glGenVertexArrays(1, &CanvasVertexArrayID);
	glBindVertexArray(CanvasVertexArrayID);
	
	CanvasShaderID = LoadShaders("mandelbrot.vertexshader", "mandelbrot.fragmentshader");
	generateRectangularVertices(
		glm::vec2(-1.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, -1.0f),
		glm::vec2(-1.0f, -1.0f));

	glGenBuffers(1, &CanvasVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, CanvasVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
	MatrixID = glGetUniformLocation(CanvasShaderID, "MVP");
	ControlsID = glGetUniformLocation(CanvasShaderID, "Controls");
}

void Canvas::drawCanvas(glm::vec4 Position)
{
	glUseProgram(CanvasShaderID);
	glm::mat4 Model = glm::translate(glm::mat4(), glm::vec3(0));
	glm::mat4 MVP = *Projection * *View * Model;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniform4f(ControlsID, Position.x, Position.y, Position.z, Position.w);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, CanvasVertexBufferID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableVertexAttribArray(0);
}

void Canvas::CleanUp()
{
	glDeleteBuffers(1, &CanvasVertexBufferID);
	glDeleteProgram(CanvasShaderID);
	glDeleteVertexArrays(1, &CanvasVertexArrayID);
}

void Canvas::generateRectangularVertices(
	glm::vec2 top_left, 
	glm::vec2 top_right,
	glm::vec2 bottom_right,
	glm::vec2 bottom_left)
{
	glm::vec2 vertex_up_left = top_left;
	glm::vec2 vertex_up_right = top_right;
	glm::vec2 vertex_down_right = bottom_right;
	glm::vec2 vertex_down_left = bottom_left;

	vertices.push_back(vertex_up_left);
	vertices.push_back(vertex_down_left);
	vertices.push_back(vertex_up_right);

	vertices.push_back(vertex_down_right);
	vertices.push_back(vertex_up_right);
	vertices.push_back(vertex_down_left);
}