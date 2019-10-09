#include <bspch.h>
#include "mesh.h"

namespace bs {

	Mesh::Mesh(std::vector<vertex> vertices, std::vector<int> indices, std::vector<Texture> textures)
		: m_Textures(textures) {

		this->m_Vao.setData(&(vertices[0].position.x), vertices.size() * sizeof(vertex));
		this->m_Ibo.setIndices((unsigned int*)indices.data(), indices.size());

		this->m_Vao.setVertexAttrib(0, 0, 3, sizeof(vertex), 0);
		this->m_Vao.setVertexAttrib(1, 1, 3, sizeof(vertex), 3);
		this->m_Vao.setVertexAttrib(2, 2, 2, sizeof(vertex), 6);

	}

	Mesh::~Mesh(){}

	void Mesh::draw(Shader shader) {
	
		uint32_t texCount = 0;

		std::vector<int> diffuseSlots;
		std::vector<int> specularSlots;
	
		for (auto texture : this->m_Textures) {

			texture.setSlot(texCount);
			texture.bind();

			switch (texture.getType()) {

			case DIFFUSE_MAP:
				diffuseSlots.push_back(texCount);
				break;
			case SPECULAR_MAP:
				specularSlots.push_back(texCount);
				break;
			default:
				break;
			
			}

			shader.setUniform1iv("diffuseSlot", diffuseSlots);
			shader.setUniform1iv("specularMaps", specularSlots);

			texCount++;
		}

		Renderer::draw(shader, this->m_Vao, this->m_Ibo);

	}



}