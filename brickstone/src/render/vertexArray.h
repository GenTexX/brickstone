#pragma once

#include <GL/glew.h>
#include "VertexBuffer.h"

namespace bs {

	class VertexArray {
	private:
		unsigned int m_ID;
		unsigned int m_Count;
		float* m_Buffer;

		VertexBuffer* m_Vbo;
			
	public:
		VertexArray();
		~VertexArray();


		unsigned int getCount();
		void setData(const float* pos, const unsigned int& size);
		void setVertexAttrib(const int& index, const int& layout, const int& vertexSize, const int& stride, const int& offset);
		float* map();
		void unmap();
		void bind();
		void unbind();
		void deleteBuffer();

		float& operator[](const int& index);

	};

}