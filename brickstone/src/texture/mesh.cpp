#include <bspch.h>
#include "mesh.h"

namespace bs {

	Mesh::Mesh(std::vector<vertex> vertices, std::vector<int> indices, std::vector<Texture> textures)
		: m_Vertices(vertices), m_Indices(indices), m_Textures(textures) {

		this->setupMesh();

	}

	Mesh::~Mesh(){}

	void Mesh::draw(Shader shader) {
	
		int diffuseCount = 0;
		int specularCount = 0;
	
		for (int i = 0; i < this->m_Textures.size(); i++) {
		}

	}



}