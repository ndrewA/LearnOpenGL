#include "Mesh.h"

#include <glad/glad.h>

#include "Platform/OpenGL/OpenGLVertexBuffer.h"
#include "Platform/OpenGL/OpenGLElementBuffer.h"
#include "Platform/OpenGL/OpenGLBufferLayout.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<Texture>& textures, const std::vector<uint32_t>& indices)
	: vertices(vertices), textures(textures), indices(indices)
{
	setupMesh();
}

void Mesh::draw(std::shared_ptr<Program> program)
{
	unsigned int diffuseNumber = 1;
	unsigned int specularNumber = 1;

	for (int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		std::string name = textures[i].type;

		std::string number;
		if (name == "texture_diffuse")
			number = diffuseNumber++;
		else if (name == "texture_sepcular")
			number = specularNumber++;

		program->setUniform((name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glActiveTexture(GL_TEXTURE0);

	vertexArray->bind();
	glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	vertexBuffer = std::make_shared<OpenGLVertexBuffer<Vertex>>(vertices);
	elementBuffer = std::make_shared<OpenGLElementBuffer>(indices);

	const std::vector<BufferLayout::LayoutElement> layoutElements = {
		{ "position", ElementType::Float3 },
		{ "normals", ElementType::Float3 },
		{ "texCoords", ElementType::Float2 }
	};

	auto layout = std::make_shared<OpenGLBufferLayout>(layoutElements);
	
	vertexArray = std::make_shared<OpenGLVertexArray>();
	vertexArray->addVertexBuffer(vertexBuffer, layout);
	vertexArray->setElementBuffer(elementBuffer);
}
