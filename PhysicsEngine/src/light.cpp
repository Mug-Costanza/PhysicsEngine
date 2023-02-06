#include "light.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <GLM/glm/gtc/type_ptr.hpp>
#include <GLM/glm/gtx/string_cast.hpp>

extern unsigned int shaderID, depthShaderID;

Light::Light(glm::vec3 posIn, glm::vec3 colorIn, int strengthIn, glm::vec3 directionIn) : Position(posIn), color(colorIn), strength(strengthIn), direction(directionIn)
{
	setUniforms();

	glEnable(GL_DEPTH_TEST);
	
	// Init shadow framebuffer.
	glGenFramebuffers(1, &depthMapBuffer);

	// Init shadow depth map.
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		sWidth, sHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//float borderColor[] = { 0.0, 0.0, 0.0, 1.0 };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE); // Prevent screen from going insane.
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Light::render()
{
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
	glm::mat4 lightView = glm::lookAt(Position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	lightMat = lightProjection * lightView;

	setUniforms();
}

unsigned int Light::getDepthMapBuffer() const
{
	return depthMapBuffer;
}

unsigned int Light::getDepthMap() const
{
	return depthMap;
}

unsigned int Light::getShadowWidth() const
{
	return sWidth;
}

unsigned int Light::getShadowHeight() const
{
	return sHeight;
}

float Light::getNearPlane()
{
	return nearPlane;
}

float Light::getFarPlane()
{
	return farPlane;
}

void Light::setUniforms()
{
	unsigned int lightPosID = glGetUniformLocation(shaderID, "lightPos");
	glUniform3f(lightPosID, Position.x, Position.y, Position.z);

	unsigned int lightColorID = glGetUniformLocation(shaderID, "lightColor");
	glUniform3f(lightColorID, color.x, color.y, color.z);

	unsigned int lightStrengthID = glGetUniformLocation(shaderID, "lightStrength");
	glUniform1f(lightStrengthID, strength);

	unsigned int lightDirectionID = glGetUniformLocation(shaderID, "lightDirection");
	glUniform3f(lightDirectionID, direction.x, direction.y, direction.z);

	unsigned int lightMatrixShaderID = glGetUniformLocation(shaderID, "lightMat");
	glUniformMatrix4fv(lightMatrixShaderID, 1, GL_FALSE, &lightMat[0][0]);

	unsigned int lightMatrixID = glGetUniformLocation(depthShaderID, "lightMat");
	glUniformMatrix4fv(lightMatrixID, 1, GL_FALSE, &lightMat[0][0]);
}
