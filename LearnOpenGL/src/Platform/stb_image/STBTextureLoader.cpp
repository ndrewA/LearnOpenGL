#include "STBTextureLoader.h"

#include <stb_image/stb_image.h>

STBTextureLoader::STBTextureLoader(const std::string& path, const bool shouldFilp)
{
	stbi_set_flip_vertically_on_load(shouldFilp);
	data = stbi_load(path.c_str(), &width, &height, &channelCount, 0);
}

STBTextureLoader::~STBTextureLoader()
{
	stbi_image_free(data);
}
