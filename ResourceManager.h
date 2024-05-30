#pragma once

#include <map>
#include <string>
#include <fstream>

#include "Shader.h"
#include "Texture2D.h"

class ResourceManager 
{
public:
	static void CreateShader(const char* vertexShaderPath, const char* fragmentShaderPath, const std::string& name);
	static void CreateTexture(const char* imagePath, unsigned int numChannels, const std::string& name, 
		GLenum textureWrapS = GL_REPEAT, GLenum textureWrapT = GL_REPEAT);

	static Shader& getShader(const std::string& name);
	static Texture2D& getTexture(const std::string& name);

private:
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture2D> textures;

	static const char* ReadShader(const char* path);
};