#pragma once

#include <iostream>
#include <GL/glew.h>

namespace bs {

	class VertexBuffer {
	private:
		unsigned int id;
	
	public:
		VertexBuffer();
		~VertexBuffer();

		void setData(const float* pos, const int& size);
		void setVertexAttrib(const int& index, const int& layout, const int& vertexSize, const int& stride, const int& offset);
		float* map();
		void unmap();
		void bind();

	};

}