#pragma once

#include <shader/shader.h>
#include <texture/material.h>
#include "VertexArray.h"
#include "IndexBuffer.h"

namespace bs {

	class Renderer {
	private:


	public:
		Renderer();
		~Renderer();

		static void draw(Shader& sho, VertexArray& vao);
		static void clear();
	};

}
