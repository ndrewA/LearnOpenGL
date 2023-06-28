#pragma once

#include <string>
#include <memory>

#include "Renderer/Texture.h"
#include "Renderer/TextureLoader.h"

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
    void setTextureProperties(const std::unique_ptr<TextureLoader>& loader);
    unsigned int determineFormat(int channelCount) const;

private:
    unsigned int textureHandle;

    int width, height, channelCount;
    const std::string filePath;
};