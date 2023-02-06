#include "object.hpp"
#include "util/objLoader.hpp"
#include "math/matrices.hpp"
#include "player.hpp"
//#include "../main.cpp"

extern unsigned int shaderID, depthShaderID;
extern glm::mat4 modelMat;
extern glm::vec3 direction;
extern Player player;

// PURPOSE : Initializes vertex arrays and buffers. Used to pass data to shaders.

Object::Object(const char* modelPath, PhysicsID id, auto in1, auto in2) : modelFile(modelPath), physicsID(id)
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

	InitPhysicsBody(in1, in2);
	rigidBody.InitRigidBody(Position, Velocity);
}

// PURPOSE : Renders object; runs in while loop in main.

void Object::render()
{
	Position = rigidBody.Position;

	modelMat = CheckMatrices(*this);

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

	unsigned int modelMatID = glGetUniformLocation(shaderID, "modelMat");
	glUniformMatrix4fv(modelMatID, 1, GL_FALSE, &modelMat[0][0]);

	unsigned int modelMatDepthID = glGetUniformLocation(depthShaderID, "modelMat");
	glUniformMatrix4fv(modelMatDepthID, 1, GL_FALSE, &modelMat[0][0]);

	unsigned int directionID = glGetUniformLocation(shaderID, "direction");
	glUniform3f(directionID, direction.x, direction.y, direction.z);

	unsigned int viewPosID = glGetUniformLocation(shaderID, "viwePos");
	glUniform3f(viewPosID, player.Position.x, player.Position.y, player.Position.z);

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

void Object::InitPhysicsBody()
{
	switch (this->physicsID)
	{
	case(BOX):


		break;
	case(SPHERE):


		break;
	case(PLANE):


		break;
	case(NULLBODY):


		break;
	}
}

void Object::ApplyGravity(float dt, glm::vec3 gravity)
{
	rigidBody.Position += gravity * dt * 3.0f;
}