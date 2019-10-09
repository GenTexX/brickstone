#include <math/maths.h>
#include <shader/shader.h>
#include <texture/texture.h>
#include <render/vertexArray.h>
#include <render/indexBuffer.h>
#include <render/renderer.h>

namespace bs {

	struct vertex {
		vec3 position;
		vec3 normal;
		ivec2 texCoord;
	};

	class Mesh {

	private:
		VertexArray m_Vao;
		IndexBuffer m_Ibo;
		std::vector<Texture> m_Textures;

		void setupMesh();

	public:
		Mesh(std::vector<vertex> vertices, std::vector<int> indices, std::vector<Texture> textures);
		~Mesh();

		void draw(Shader shader);

	};

}