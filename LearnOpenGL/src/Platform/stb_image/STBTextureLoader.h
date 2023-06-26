#pragma once

#include <string>

#include "Renderer/TextureLoader.h"

class STBTextureLoader : public TextureLoader
{
public:
	STBTextureLoader(const std::string& path, const bool shouldFilp = true);

	~STBTextureLoader() override;

	unsigned char* getData() const override { return data; }
	int getWidth() const override { return width; }
	int getHeight() const override { return height; }
	int getChannelCount() const override { return channelCount; }

private:
	unsigned char* data;
	int width, height, channelCount;
};

