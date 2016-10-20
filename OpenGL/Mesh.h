#pragma once

#include <string>
#include <vector>

#include <glm.hpp>

#include <assimp/Importer.hpp>

#include <GL\glew.h>

#include "Shader.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	std::string type;
	aiString path;
};

class Mesh {
public:	
	std::vector<Vertex> _vertices;
	std::vector<GLuint> _indices;
	std::vector<Texture> _textures;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	void Draw(Shader shader);
	GLuint getVAO();
private:
	GLuint _VAO, _VBO, _EBO;
	void setupMesh();
};

