#pragma once

#include <string>

class TextureLoader
{
public:
	virtual ~TextureLoader() = default;

	virtual unsigned char* getData() const = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
	virtual int getChannelCount() const = 0;
};