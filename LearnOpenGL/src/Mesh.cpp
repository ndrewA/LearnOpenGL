#include "Mesh.h"

#include <glad/glad.h>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<Texture>& textures, const std::vector<uint32_t>& indices)
	: vertices(vertices), textures(textures), indices(indices)
{
	setupMesh();
}

void Mesh::draw(const Shader& shader)
{
	uint32_t diffuseNumber = 1;
	uint32_t specularNumber = 1;

	for (uint32_t i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		std::string name = textures[i].type;

		std::string number;
		if (name == "texture_diffuse")
			number = diffuseNumber++;
		else if (name == "texture_sepcular")
			number = specularNumber++;

		shader.setInt((name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
}
