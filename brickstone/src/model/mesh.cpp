#include <bspch.h>
#include "mesh.h"

namespace bs {

	Mesh::Mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
		 : vertices(vertices), indices(indices), textures(textures) {

		this->setupMesh();
	}

	Mesh::~Mesh(){}

	void Mesh::draw(Shader shader) {
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
	
		for (int i = 0; i < this->textures.size(); i++) {

			glActiveTexture(GL_TEXTURE0 + 1);

			std::string number;
			TextureType t = this->textures[i].getType();

			switch (t) {
			case DIFFUSE_MAP:
				number = std::to_string(diffuseNr++);
				shader.setUniform1i(("material.diffuseMap." + number).c_str(), i);
				break;

			case SPECULAR_MAP:
				number = std::to_string(specularNr++);
				shader.setUniform1i(("material.specularMap." + number).c_str(), i);
				break;

			default:
				break;
			}

			this->textures[i].setSlot(i);
			this->textures[i].bind();

		}

		glBindVertexArray(this->vao);
		glDrawElements(GL_TRIANGLES, (GLsizei) this->indices.size(), GL_UNSIGNED_INT, 0);

	}

	void Mesh::setupMesh() {

		glGenVertexArrays(1, &(this->vao));
		glGenBuffers(1, &(this->vbo));
		glGenBuffers(1, &(this->ebo));

		glBindVertexArray(this->vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(vertex), &(this->vertices[0]), GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &(this->indices[0]), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*) 0);
		
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*) offsetof(vertex, normal));
		
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*) offsetof(vertex, texCoord));

	}

}