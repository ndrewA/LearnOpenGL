#pragma once

#include <unordered_map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

class Model
{
public:
	Model(const std::string& path);

	void draw(const Shader& shader);

private:
	std::vector<Mesh> meshes;
	std::string directory;
	std::unordered_map<std::string, Texture> loadedTextures;

private:
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);

	uint32_t textureFromFile(const std::string& relativePath);
};

