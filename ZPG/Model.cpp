#include "Model.h"

// Include GLAD
#include <glad/gl.h>

Model::Model(const float* data, unsigned int vertexCount, unsigned int floatPerVertex, bool hasNormal, bool hasColor, bool coloreBeforeNormal)
	: vertexCount_(vertexCount)
{
	// vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount_ * floatPerVertex * sizeof(float), data, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &vao_); //generate the VAO
	glBindVertexArray(vao_); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes

	GLuint offset = 0;
	// index, number of components, data type, normalized, vertex stride, offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, floatPerVertex * sizeof(float), (GLvoid*)0);
	offset += 3;

	//color berore normal???
	if (coloreBeforeNormal) {
		if (hasColor) {
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, floatPerVertex * sizeof(float), (GLvoid*)(offset * sizeof(float)));
			offset += 3;
		}
		else {
			glDisableVertexAttribArray(2);
		}

		if (hasNormal) {
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, floatPerVertex * sizeof(float),(GLvoid*)(offset * sizeof(float)));
		}
		else {
			glDisableVertexAttribArray(1);
		}
	}
	else {
		if (hasNormal) {
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, floatPerVertex * sizeof(float), (GLvoid*)(offset * sizeof(float)));
			offset += 3;
		}
		else {
			glDisableVertexAttribArray(1);
		}

		if (hasColor) {
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, floatPerVertex * sizeof(float),(GLvoid*)(offset * sizeof(float)));
		}
		else {
			glDisableVertexAttribArray(2);
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Model::draw() const
{
	glBindVertexArray(vao_);

	// Draw a triangles
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_); //mode,first,count
}