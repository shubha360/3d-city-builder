#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <iostream>

class Shader 
{
public:
	Shader(const char* shaderName, const char* vertexData, const char* fragmentData);
	~Shader();

	void use() const;
	void unuse() const;
	
	void setI(const char* uniformName, const int value, bool useShader = false);

	void set2f(const char* uniformName, const float value1, const float value2, bool useShader = false);
	void set2f(const char* uniformName, const glm::vec2& vector, bool useShader = false);

	void set3f(const char* uniformName, const float value1, const float value2, const float value3, bool useShader = false);
	void set3f(const char* uniformName, const glm::vec3& vector, bool useShader = false);

	void set4f(const char* uniformName, const float value1, const float value2, const float value3, const float value4, bool useShader = false);
	void set4f(const char* uniformName, const glm::vec4& vector, bool useShader = false);

	void setMat4(const char* uniformName, const glm::mat4& matrix, bool useShader = false);

private:
	unsigned int id = 0;
	const char* name = nullptr;

	unsigned int compileShader(const GLenum shaderType, const char* shaderData);
	void checkCompilationStatus(const unsigned int shaderID, GLenum shaderType);
	void checkLinkingStatus();
	int findUniformLocation(const char* uniformName);
};