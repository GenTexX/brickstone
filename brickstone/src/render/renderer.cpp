#include <bspch.h>
#include "Renderer.h"

namespace bs {

	Renderer::Renderer() {

	}

	Renderer::~Renderer() {

	}

	void Renderer::draw(Shader& sho, VertexArray& vao) {

		sho.bind();
		vao.bind();

		glDrawArrays(GL_TRIANGLES, 0, vao.getCount()/6);

	}

	void Renderer::clear() {
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	}
}