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
		vec2 texCoord;
	};

	class Mesh {

	private:
		unsigned int vao, vbo, ebo;

		void setupMesh();

	public:
		std::vector<vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		Mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		~Mesh();

		void draw(Shader shader);

	};

}