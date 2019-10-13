#include <bspch.h>
#include "mesh.h"

namespace bs {

	Mesh::Mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, Material *material)
		 : m_Vertices(vertices), m_Indices(indices), m_Material(material) {

		this->setupMesh();
	}

	Mesh::~Mesh() { delete this->m_Material; }

	void Mesh::draw(Shader shader) {
		
		shader.setUniformMaterial(*m_Material);
		glBindVertexArray(this->vao);
		glDrawElements(GL_TRIANGLES, (GLsizei) this->m_Indices.size(), GL_UNSIGNED_INT, 0);

	}

	void Mesh::setupMesh() {

		glGenVertexArrays(1, &(this->vao));
		glGenBuffers(1, &(this->vbo));
		glGenBuffers(1, &(this->ebo));

		glBindVertexArray(this->vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

		glBufferData(GL_ARRAY_BUFFER, this->m_Vertices.size() * sizeof(vertex), &(this->m_Vertices[0]), GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_Indices.size() * sizeof(unsigned int), &(this->m_Indices[0]), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*) 0);
		
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*) offsetof(vertex, normal));
		
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*) offsetof(vertex, texCoord));

	}

}