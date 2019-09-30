#pragma once

#include <GL/glew.h>
#include "VertexBuffer.h"

namespace bs {

	class VertexArray {
	private:
		unsigned int id;

		int count;

		float* buffer;
			
	public:
		VertexArray();
		~VertexArray();

		VertexBuffer *vbo;

		int getCount();
		void setData(const float* pos, const int& size);
		void setVertexAttrib(const int& index, const int& layout, const int& vertexSize, const int& stride, const int& offset);
		float* map();
		void unmap();
		void bind();
		void unbind();

		float& operator[](const int& index);

	};

}