#include <bspch.h>
#include "VertexBuffer.h"

namespace bs {

	VertexBuffer::VertexBuffer() {

		glGenBuffers(1, &(this->m_ID));

	}

	VertexBuffer::~VertexBuffer() {

	}

	void VertexBuffer::setData(const float* pos, const unsigned int& size) {

		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), pos, GL_STATIC_DRAW);

	}

	void VertexBuffer::setVertexAttrib(const int& index, const int& layout, const unsigned int& vertexSize, const unsigned int& stride, const unsigned int& offset) {

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(layout, vertexSize, GL_FLOAT, GL_FALSE, stride * sizeof(float), (const void*)(offset * sizeof(float)));

	}

	float* VertexBuffer::map() {
		return (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
	}

	void VertexBuffer::unmap() {

		glUnmapBuffer(GL_ARRAY_BUFFER);

	}

	void VertexBuffer::bind() {

		glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);

	}

	void VertexBuffer::deleteBuffer() {

		glDeleteBuffers(1, &(this->m_ID));
		glGenBuffers(1, &(this->m_ID));

	}

}