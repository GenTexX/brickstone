#pragma once

#include <math/maths.h>
#include <shader/shader.h>
#include <model/texture.h>
#include <render/vertexArray.h>
#include <render/indexBuffer.h>
#include <render/renderer.h>

namespace bs {

	struct vertex {
		vec3 position;
		vec3 normal;
		vec2 texCoord;
	};

	class Mesh {

	private:
		VertexArray m_VAO;
		IndexBuffer m_IBO;


	public:
		std::vector<vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		Material* m_Material;

		Mesh();
		Mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, Material *material);
		~Mesh();

		void draw(Shader shader);
		void setupMesh();

	};

}