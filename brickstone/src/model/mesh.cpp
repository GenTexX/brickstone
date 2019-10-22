#include <bspch.h>
#include "mesh.h"

namespace bs {
	Mesh::Mesh()
	{
	}
	Mesh::Mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, Material *material)
		 : m_Vertices(vertices), m_Indices(indices), m_Material(material), m_VAO(), m_IBO() {

		this->setupMesh();
	}

	Mesh::~Mesh() { delete this->m_Material; }

	void Mesh::draw(Shader shader) {
		
		shader.setUniformMaterial(*m_Material);
		this->m_VAO.bind();
		glDrawElements(GL_TRIANGLES, (GLsizei) this->m_Indices.size(), GL_UNSIGNED_INT, 0);

	}

	void Mesh::setupMesh() {


		//set Vertices
		this->m_VAO.bind();
		this->m_VAO.setData(&(this->m_Vertices[0]).position.x, (const unsigned int) this->m_Vertices.size() * 8);

		//set Indices
		this->m_IBO.bind();
		this->m_IBO.setIndices(&(this->m_Indices[0]), (int)this->m_Indices.size());
		
		//Positions
		this->m_VAO.setVertexAttrib(0, 0, 3, sizeof(vertex) / sizeof(float), 0);

		//NormalVectors
		this->m_VAO.setVertexAttrib(1, 1, 3, sizeof(vertex) / sizeof(float), offsetof(vertex, normal) / sizeof(float));

		//TextureCoordinates
		this->m_VAO.setVertexAttrib(2, 2, 2, sizeof(vertex) / sizeof(float), offsetof(vertex, texCoord) / sizeof(float));


	}

}