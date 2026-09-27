#include "Model.h"

// Include GLAD
#include <glad/gl.h>

Model::Model(const float* data, unsigned int vertexCount)
	: vertexCount_(vertexCount)
{
	// vertex buffer object (VBO)
	unsigned int VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount_ * 6 * sizeof(float), data, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &vao_); //generate the VAO
	glBindVertexArray(vao_); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// index, number of components, data type, normalized, vertex stride, offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}

void Model::draw() const
{
	glBindVertexArray(vao_);

	// Draw a triangles
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_); //mode,first,count
}
