#include "VertexBuffer.h"

namespace bs {

	VertexBuffer::VertexBuffer() {

		glGenBuffers(1, &(this->id));

	}

	VertexBuffer::~VertexBuffer() {

	}

	void VertexBuffer::setData(const float* pos, const int& size) {

		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), pos, GL_STATIC_DRAW);

	}

	void VertexBuffer::setVertexAttrib(const int& index, const int& layout, const int& vertexSize, const int& stride, const int& offset) {

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

		glBindBuffer(GL_ARRAY_BUFFER, this->id);

	}

}