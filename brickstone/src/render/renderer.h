#pragma once

#include <shader/shader.h>
#include <model/material.h>
#include "VertexArray.h"
#include "IndexBuffer.h"

namespace bs {

	class Renderer {
	private:


	public:
		Renderer();
		~Renderer();

		static void draw(Shader& sho, VertexArray& vao, IndexBuffer& ibo);
		static void clear();
	};

}
