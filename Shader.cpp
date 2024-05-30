#include "Shader.h"

Shader::Shader(const char* shaderName, const char* vertexData, const char* fragmentData) 
	: name(shaderName)
{
	
	unsigned int vShader = compileShader(GL_VERTEX_SHADER, vertexData);
	unsigned int fShader = compileShader(GL_FRAGMENT_SHADER, fragmentData);

	this->id = glCreateProgram();

	glAttachShader(this->id, vShader);
	glAttachShader(this->id, fShader);

	glLinkProgram(this->id);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

Shader::~Shader() 
{
	if (this->id != 0) 
	{
		glDeleteShader(this->id);
		this->id = 0;
	}
}

void Shader::use() const 
{
	if (id != 0)
		glUseProgram(id);
}

void Shader::unuse() const 
{
	if (id != 0)
		glUseProgram(0);
}

void Shader::setI(const char* uniformName, const int value, bool useShader) 
{
	if (useShader)
		this->use();

	int location = this->findUniformLocation(uniformName);

	if (location != -1)
		glUniform1i(location, value);
}

void Shader::set2f(const char* uniformName, const float value1, const float value2, bool useShader) 
{
	if (useShader)
		this->use();

	int location = this->findUniformLocation(uniformName);

	if (location != -1)
		glUniform2f(location, value1, value2);
}

void Shader::set2f(const char* uniformName, const glm::vec2& vector, bool useShader) 
{
	if (useShader)
		this->use();

	int location = this->findUniformLocation(uniformName);

	if (location != -1)
		glUniform2f(location, vector.x, vector.y);
}

void Shader::set3f(const char* uniformName, const float value1, const float value2, const float value3, bool useShader) 
{
	if (useShader)
		this->use();

	int location = this->findUniformLocation(uniformName);

	if (location != -1)
		glUniform3f(location, value1, value2, value3);
}

void Shader::set3f(const char* uniformName, const glm::vec3& vector, bool useShader) 
{
	if (useShader)
		this->use();

	int location = this->findUniformLocation(uniformName);

	if (location != -1)
		glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::set4f(const char* uniformName, const float value1, const float value2, const float value3, const float value4, bool useShader) 
{
	if (useShader)
		this->use();

	int location = this->findUniformLocation(uniformName);

	if (location != -1)
		glUniform4f(location, value1, value2, value3, value4);
}

void Shader::set4f(const char* uniformName, const glm::vec4& vector, bool useShader) 
{
	if (useShader)
		this->use();

	int location = this->findUniformLocation(uniformName);

	if (location != -1)
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void Shader::setMat4(const char* uniformName, const glm::mat4& matrix, bool useShader) 
{
	if (useShader)
		this->use();

	int location = this->findUniformLocation(uniformName);

	if (location != -1)
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

unsigned int Shader::compileShader(const GLenum shaderType, const char* shaderData) 
{
	unsigned int shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderData, nullptr);
	glCompileShader(shaderID);
	checkCompilationStatus(shaderID, shaderType);

	return shaderID;
}

void Shader::checkCompilationStatus(const unsigned int shaderID, GLenum shaderType) 
{
	int success;
	char infoLog[1024];

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success) 
	{
		glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);

		const char* shaderName = shaderType == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader";

		std::cout << "Error compiling " << shaderName << "\n"
			<< infoLog << "\n\n";
	}
}

void Shader::checkLinkingStatus() 
{
	int success;
	char infoLog[1024];

	glGetProgramiv(this->id, GL_LINK_STATUS, &success);

	if (!success) 
	{
		glGetProgramInfoLog(this->id, 1024, nullptr, infoLog);

		std::cout << "Error linking " << name << " shader program.\n"
			<< infoLog << "\n\n";
	}
}

int Shader::findUniformLocation(const char* uniformName) 
{
	
	int location = glGetUniformLocation(this->id, uniformName);

	if (location == -1)
		printf("Could not find uniform named %s in the %s shader!", uniformName, this->name);
	
	return location;
}
