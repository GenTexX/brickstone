#include <bspch.h>
#include "Renderer.h"

namespace bs {

	Renderer::Renderer() {

	}

	Renderer::~Renderer() {

	}

	void Renderer::draw(Shader& sho, VertexArray& vao, IndexBuffer& ibo) {

		sho.bind();
		vao.bind();
		ibo.bind();

		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);

	}

	void Renderer::clear() {
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	}
}