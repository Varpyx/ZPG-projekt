#include "Model.h"

// Include GLAD
#include <glad/gl.h>

Model::Model(const float* data, unsigned int vertexCount, unsigned int floatPerVertex)
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
	// index, number of components, data type, normalized, vertex stride, offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, floatPerVertex * sizeof(float), (GLvoid*)0);

	if (floatPerVertex >= 6) {
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, floatPerVertex * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	}

	if (floatPerVertex >= 9) {
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,floatPerVertex * sizeof(float),(GLvoid*)(6 * sizeof(float)));
	}
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Model::draw() const
{
	glBindVertexArray(vao_);

	// Draw a triangles
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_); //mode,first,count
}