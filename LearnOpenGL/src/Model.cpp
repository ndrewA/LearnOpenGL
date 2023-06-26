#include "Model.h"

#include <iostream>
#include <memory>

#include <glad/glad.h>

#include "Platform/stb_image/STBTextureLoader.h"

Model::Model(const std::string& path)
{
    loadModel(path);
}

void Model::draw(const std::shared_ptr<Program>& program)
{
    for (auto& mesh : meshes)
        mesh.draw(program);
}

void Model::loadModel(std::string path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "Assmip error: " << importer.GetErrorString() << '\n';
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (uint32_t i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.emplace_back(processMesh(mesh, scene));
    }

    for (uint32_t i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene);
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    std::vector<uint32_t> indices;

    for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
        glm::vec3 position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
        glm::vec3 normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

        Vertex vertex{ position, normal };

        if (mesh->mTextureCoords[0]) {
            glm::vec2 texCoords;
            texCoords.x = mesh->mTextureCoords[0][i].x;
            texCoords.y= mesh->mTextureCoords[0][i].y;

            vertex.texCoords = texCoords;
        }
        else {
            vertex.texCoords = { 0.f, 0.f };
        }

        vertices.emplace_back(vertex);
    }

    if (mesh->mMaterialIndex >= 0) {

    }

    for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (uint32_t j = 0; j < face.mNumIndices; j++) {
            indices.emplace_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return { vertices, textures, indices };
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
        aiString str;
        material->GetTexture(type, i, &str);

        if (loadedTextures.find(str.C_Str()) != loadedTextures.end()) {
            textures.emplace_back(loadedTextures[str.C_Str()]);
        }
        else {
            Texture texture;
            texture.id = textureFromFile(str.C_Str());
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.emplace_back(texture);
            loadedTextures.insert({ texture.path, texture});
        }
    }
    return textures;
}

uint32_t Model::textureFromFile(const std::string& relativePath)
{
    const std::string absolutePath = directory + '/' + relativePath;

    auto loader = std::make_unique<STBTextureLoader>(absolutePath);

    if (loader->getData() == nullptr)
        throw std::exception("Texture did NOT load!");

    unsigned int format = GL_RGBA;
    switch (loader->getChannelCount())
    {
    case 1:
        format = GL_RED;
        break;
    case 2:
        format = GL_RG;
        break;
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
        break;
    default:
        throw std::runtime_error("channelCount > 4 unsupported!");
    }

    unsigned int textureHandle;
    glGenTextures(1, &textureHandle);

    glBindTexture(GL_TEXTURE_2D, textureHandle);

    glTexImage2D(GL_TEXTURE_2D, 0, format, loader->getWidth(), loader->getHeight(), 0, format, GL_UNSIGNED_BYTE, loader->getData());

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return textureHandle;
}
