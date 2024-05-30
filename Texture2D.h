#pragma once

#include <GL/glew.h>
#include <stb_image/stb_image.h>
#include <iostream>

class Texture2D 
{
public:
	Texture2D(const char* path, unsigned int numChannels, GLenum textureWrapS = GL_REPEAT, GLenum textureWrapT = GL_REPEAT);
	~Texture2D();

	void bind();
	void unbind();

	unsigned char* data = nullptr;
	unsigned int id = 0;
	int width = 0, height = 0;
	int nChannels = 0, nChannelsInFile = 0;
};