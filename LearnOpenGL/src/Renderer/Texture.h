#pragma once

class Texture
{
public:
	virtual ~Texture() = default;

	virtual void bind(const unsigned int slot = 0) const = 0;
	virtual void unbind() const = 0;

	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
};