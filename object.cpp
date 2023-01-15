#include "object.hpp"
#include "objLoader.hpp"
#include "matrices.hpp"

extern unsigned int shaderID, depthShaderID;
extern glm::mat4 modelMat;

// PURPOSE : Initializes vertex arrays and buffers.

Object::Object(const char* modelPath) : modelFile(modelPath)
{
	LoadOBJ(modelPath, vertices, textureCoords, normals);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(glm::vec3), &textureCoords[0], GL_STATIC_DRAW);

	initPhysicsBody();
}

// PURPOSE : Renders object; runs in while loop in main.

void Object::render()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() * 3);
	glDisableVertexAttribArray(0);

	modelMat = CheckMatrices(*this);

	unsigned int modelMatID = glGetUniformLocation(shaderID, "modelMat");
	glUniformMatrix4fv(modelMatID, 1, GL_FALSE, &modelMat[0][0]);

	unsigned int modelMatDepthID = glGetUniformLocation(depthShaderID, "modelMat");
	glUniformMatrix4fv(modelMatDepthID, 1, GL_FALSE, &modelMat[0][0]);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Object::destroy()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &normalBuffer);
	glDeleteBuffers(1, &textureBuffer);
}

void Object::initPhysicsBody()
{
	switch (physicsID)
	{
	case(RigidBody):
		initRigidBody();

		break;
	case(SoftBody):
		initSoftBody();

		break;
	case(LiquidBody):
		initLiquidBody();

		break;
	}
}

void Object::initRigidBody()
{
	inverseMass = 1.0f / Mass;
}

void Object::initSoftBody()
{
	   
}

void Object::initLiquidBody()
{

}