#pragma once

#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"

enum class TextureType
{
	Diffuse,
	Specular,
	Normal,
	AmbientOcclusion,
	Emissive,
	Height,
	Roughness,
	Metallic
};

class Material
{
public:
	Material() { }

	bool hasTexture(const TextureType type) const { return textures.find(type) != textures.end(); }
	
	const glm::vec3& getColor() const { return color; }
	const std::shared_ptr<Texture>& getTexture(const TextureType type) const 
	{
		if (textures.find(type) == textures.end())
			throw std::exception("texture not found!");
		return textures[type]; 
	}
	const float getSpecularity() const { return specularity; }

	void setColor(const glm::vec3& color) { this->color = color; }
	void addTexture(const TextureType type, const std::shared_ptr<Texture>& texture) { textures[type] = texture; }
	void setSpecularity(const float specularity) { this->specularity = specularity; }

private:
	glm::vec3 color = { 0.f, 0.f, 0.f };
	mutable std::unordered_map<TextureType, std::shared_ptr<Texture>> textures;
	float specularity = 0.f;
};