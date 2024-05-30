#include "Texture2D.h"

Texture2D::Texture2D(const char* path, unsigned int numChannels, GLenum textureWrapS, GLenum textureWrapT) 
	: nChannels(numChannels)
{
	this->data = stbi_load(path, &this->width, &this->height, &this->nChannelsInFile, this->nChannels);

	if (this->data == nullptr)
	{
		std::printf("Failed to load texture at %s\n", path);
	}
	else 
	{
		glGenTextures(1, &this->id);

		this->bind();

		GLint internalFormat = 0;
		GLenum format = 0;

		switch (this->nChannels) {
		
		case 1:
			internalFormat = GL_RED;
			format = GL_RED;
			break;

		case 3:
			internalFormat = GL_RGB8;
			format = GL_RGB;
			break;

		case 4:
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
			break;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, static_cast<const void*>(this->data));

		if (internalFormat == GL_RED && format == GL_RED) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_RED);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_RED);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		this->unbind();

		stbi_image_free(this->data);
	}
}

Texture2D::~Texture2D()
{
	if (this->id) 
	{
		glDeleteTextures(1, &this->id);
	}
}

void Texture2D::bind() 
{
	glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture2D::unbind() 
{
	glBindTexture(GL_TEXTURE_2D, 0);
}