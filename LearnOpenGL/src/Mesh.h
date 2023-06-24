#pragma once

#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLProgram.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"
#include "Platform/OpenGL/OpenGLElementBuffer.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture
{
	uint32_t id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	std::vector<uint32_t> indices;

	Mesh(const std::vector<Vertex>& vertices, const std::vector<Texture>& textures, const std::vector<uint32_t>& indices);
	void draw(const std::shared_ptr<Program>& program);

private:
	std::shared_ptr<VertexArray> vertexArray;
	std::shared_ptr<VertexBuffer<Vertex>> vertexBuffer;
	std::shared_ptr<ElementBuffer> elementBuffer;

	void setupMesh();
};

