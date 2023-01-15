#include "shaderLoader.hpp"

void Compile_Shader(Shader* shader);

// PURPOSE : Instructs OpenGL to interpret the shader files.
unsigned int LoadShader(const char* vPath, const char* fPath)
{
	unsigned int vertexID = glCreateShader(GL_VERTEX_SHADER),
		fragID = glCreateShader(GL_FRAGMENT_SHADER);

	int result = GL_FALSE,
		infoLogLength;

	std::string vertexPathString = vPath,
		fragmentPathString = fPath;

	std::ifstream vPathID, fragPathID;

	vPathID.open(vertexPathString);
	fragPathID.open(fragmentPathString);

	if (fragPathID.is_open())
	{
		std::stringstream sstr;
		sstr << fragPathID.rdbuf();
		fragmentPathString = sstr.str();
		fragPathID.close();
	}
	else
	{
		std::cout << "The fragment shader failed to open." << std::endl;
		return 0;
	}

	if (vPathID.is_open())
	{
		std::stringstream sstr;
		sstr << vPathID.rdbuf();
		vertexPathString = sstr.str();
		vPathID.close();
	}
	else
	{
		std::cout << "The vertex shader failed to open." << std::endl;
		return 0;
	}

	Shader vertexShader, fragmentShader;

	vertexShader.pathID = vertexPathString.c_str();
	fragmentShader.pathID = fragmentPathString.c_str();

	vertexShader.shaderID = vertexID;
	fragmentShader.shaderID = fragID;

	vertexShader.ID = "Vertex Shader";
	fragmentShader.ID = "Fragment Shader";

	Compile_Shader(&vertexShader);
	Compile_Shader(&fragmentShader);

	unsigned int programID = glCreateProgram();

	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength)
	{
		std::vector <char> error(infoLogLength + 1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &error[0]);
		std::cout << "Shader : " << &error[0] << std::endl;
	}

	glDetachShader(programID, vertexID);
	glDetachShader(programID, fragID);

	glDeleteShader(vertexID);
	glDeleteShader(fragID);

	return programID;
}

// PURPOSE : I don't feel like writing this again, lol.
void Compile_Shader(Shader* shader)
{
	int result = GL_FALSE, infoLogLength;

	const char* shaderPointer = shader->pathID;
	glShaderSource(shader->shaderID, 1, &shaderPointer, NULL);
	glCompileShader(shader->shaderID);

	glGetShaderiv(shader->shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader->shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)
	{
		std::vector <char> error(infoLogLength + 1);
		glGetShaderInfoLog(shader->shaderID, infoLogLength, NULL, &error[0]);
		std::cout << shader->ID << " " << &error[0] << std::endl;
	}
}