#include <bspch.h>
#include "VertexArray.h"

namespace bs {

	VertexArray::VertexArray() {

		glGenVertexArrays(1, &(this->m_ID));
		this->m_Vbo = new VertexBuffer();
		this->bind();
		this->m_Vbo->bind();

	}

	VertexArray::~VertexArray() {

		glDeleteVertexArrays(1, &(this->m_ID));

	}

	unsigned int VertexArray::getCount() {

		return this->m_Count;

	}

	void VertexArray::setData(const float* pos, const unsigned int& size) {

		this->m_Count = size;
		this->m_Vbo->bind();
		this->m_Vbo->setData(pos, size);

	}

	void VertexArray::setVertexAttrib(const int& index, const int& layout, const int& vertexSize, const int& stride, const int& offset) {

		this->m_Vbo->bind();
		this->m_Vbo->setVertexAttrib(index, layout, vertexSize, stride, offset);

	}

	float* VertexArray::map() {

		this->m_Vbo->bind();
		this->m_Buffer = this->m_Vbo->map();

		return this->m_Buffer;

	}

	void VertexArray::unmap() {

		this->m_Vbo->unmap();

	}

	void VertexArray::bind() {

		glBindVertexArray(this->m_ID);

	}

	void VertexArray::unbind() {

		glBindVertexArray(0);

	}

	float& VertexArray::operator[](const int& index) {

		return m_Buffer[index];

	}

}