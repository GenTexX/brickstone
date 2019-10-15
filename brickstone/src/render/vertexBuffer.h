#pragma once

#include <iostream>
#include <GL/glew.h>

namespace bs {

	class VertexBuffer {
	private:
		unsigned int m_ID;
	
	public:
		VertexBuffer();
		~VertexBuffer();

		void setData(const float* pos, const unsigned int& size);
		void setVertexAttrib(const int& index, const int& layout, const unsigned int& vertexSize, const unsigned int& stride, const unsigned int& offset);
		float* map();
		void unmap();
		void bind();
		void deleteBuffer();

	};

}