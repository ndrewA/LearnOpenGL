#pragma once

#include <memory>
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"

enum TextureType
{
	Diffuse	= 0,
	Specular,
	Normal,
	AmbientOcclusion,
	Emissive,
	Height,
	Roughness,
	Metallic,
	NUMBER_OF_TEXTURE_TYPES		
};

class Material
{
public:
	bool hasTexture(TextureType type) const { return textures[type] != nullptr; }
	
	glm::vec3 getColor() const { return color; }
	std::shared_ptr<Texture> getTexture(TextureType type) const
	{
		if (textures[type] == nullptr)
			throw std::exception("texture not found!");
		return textures[type]; 
	}
	float getSpecularity() const { return specularity; }

	void setColor(glm::vec3 color) { this->color = color; }
	void addTexture(TextureType type, std::shared_ptr<Texture> texture) { textures[type] = texture; }
	void setSpecularity(float specularity) { this->specularity = specularity; }

private:
	glm::vec3 color = { 0.f, 0.f, 0.f };
	std::array<std::shared_ptr<Texture>, NUMBER_OF_TEXTURE_TYPES> textures;
	float specularity = 0.f;
};