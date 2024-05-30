#include "ResourceManager.h"

void ResourceManager::CreateShader(const char* vertexShaderPath, const char* fragmentShaderPath, const std::string& name) 
{
	auto mapIt = shaders.find(name);

	if (mapIt != shaders.end()) 
	{
		std::printf("A shader named %s already exists!\n", name.c_str());
	}
	else 
	{
		const char* vertexShaderData = ReadShader(vertexShaderPath);
		const char* fragmentShaderData = ReadShader(fragmentShaderPath);

		Shader shader(vertexShaderData, fragmentShaderData, name.c_str());

		shaders.insert(std::make_pair(name, shader));
	}
}

void ResourceManager::CreateTexture(const char* imagePath, unsigned int numChannels, const std::string& name, GLenum textureWrapS, GLenum textureWrapT) 
{	
	auto mapIt = textures.find(name);

	if (mapIt != textures.end()) 
	{
		std::printf("A texture named %s already exists!\n", name.c_str());
	}
	else 
	{
		Texture2D texture(imagePath, numChannels, textureWrapS, textureWrapT);

		textures.insert(make_pair(name, texture));
	}
}

Shader& ResourceManager::getShader(const std::string& name) 
{
	return shaders[name];
}

Texture2D& ResourceManager::getTexture(const std::string& name) 
{
	return textures[name];
}

const char* ResourceManager::ReadShader(const char* path) 
{
	std::string data;

	std::ifstream file(path);

	if (file.is_open()) 
	{
		data = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	}
	else 
	{
		printf("Error opening file at %s\n", path);
	}

	return data.c_str();
}