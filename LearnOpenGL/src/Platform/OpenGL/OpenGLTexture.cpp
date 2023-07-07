#include "OpenGLTexture.h"

#include <memory>

#include <glad/glad.h>

#include "Platform/stb_image/STBTextureLoader.h"

OpenGLTexture::OpenGLTexture(const std::string& path)
	: filePath(filePath)
{
	std::unique_ptr<TextureLoader> loader = std::make_unique<STBTextureLoader>(path);

	if (loader->getData() == nullptr)
		throw std::exception("Texture did NOT load!");

	setTextureProperties(std::move(loader));
}

void OpenGLTexture::setTextureProperties(std::unique_ptr<TextureLoader> loader)
{
	width = loader->getWidth();
	height = loader->getHeight();
	channelCount = loader->getChannelCount();

	unsigned int format = determineFormat(channelCount);

	glGenTextures(1, &textureHandle);

	glBindTexture(GL_TEXTURE_2D, textureHandle);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, loader->getData());

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

unsigned int OpenGLTexture::determineFormat(int channelCount) const
{
	switch (channelCount)
	{
	case 1: return GL_RED;
	case 2: return GL_RG;
	case 3: return GL_RGB;
	case 4: return GL_RGBA;
	}
	throw TextureFormatNotSupported(channelCount);
}

OpenGLTexture::~OpenGLTexture()
{
	glDeleteTextures(1, &textureHandle);
}

void OpenGLTexture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
}

void OpenGLTexture::unbind() const
{
	glActiveTexture(GL_TEXTURE0);
}