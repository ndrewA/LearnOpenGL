#pragma once

#include <string>
#include <memory>
#include <stdexcept>

#include "Renderer/Texture.h"
#include "Renderer/TextureLoader.h"

class TextureFormatNotSupported : std::runtime_error
{
public:
    TextureFormatNotSupported(int channelCount)
        : runtime_error("Format with: " + std::to_string(channelCount) + " channels not supported!")
    { }
};

class OpenGLTexture : public Texture
{
public:
    OpenGLTexture(const std::string& path);
    ~OpenGLTexture() override;

    void bind(unsigned int slot = 0) const override;
    void unbind() const override;

    int getWidth() const override { return width; }
    int getHeight() const override { return height; }

private:
    void setTextureProperties(std::unique_ptr<TextureLoader> loader);
    unsigned int determineFormat(int channelCount) const;

private:
    unsigned int textureHandle;

    int width, height, channelCount;
    std::string filePath;
};