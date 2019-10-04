#include <bspch.h>
#include "VertexArray.h"

namespace bs {

	VertexArray::VertexArray() {

		glGenVertexArrays(1, &(this->id));
		this->vbo = new VertexBuffer();
		this->bind();
		this->vbo->bind();

	}

	VertexArray::~VertexArray() {

		glDeleteVertexArrays(1, &(this->id));

	}

	int VertexArray::getCount() {
		return this->count;
	}

	void VertexArray::setData(const float* pos, const int& size) {

		this->count = size;
		this->vbo->bind();
		this->vbo->setData(pos, size);

	}

	void VertexArray::setVertexAttrib(const int& index, const int& layout, const int& vertexSize, const int& stride, const int& offset) {

		this->vbo->bind();
		this->vbo->setVertexAttrib(index, layout, vertexSize, stride, offset);

	}

	float* VertexArray::map() {

		this->vbo->bind();
		this->buffer = this->vbo->map();
		return this->buffer;

	}

	void VertexArray::unmap() {

		this->vbo->unmap();

	}

	void VertexArray::bind() {

		glBindVertexArray(this->id);

	}

	void VertexArray::unbind() {

		glBindVertexArray(0);

	}

	float& VertexArray::operator[](const int& index) {

		return buffer[index];

	}

}