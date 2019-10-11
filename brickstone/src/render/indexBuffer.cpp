#include <bspch.h>
#include "IndexBuffer.h"

namespace bs {

	IndexBuffer::IndexBuffer() {

		glGenBuffers(1, &(this->m_ID));

	}

	IndexBuffer::~IndexBuffer() {

	}

	int IndexBuffer::getCount() {
		return this->m_Count;
	}

	void IndexBuffer::setIndices(unsigned int* ind, const int& cnt) {

		this->m_Count = cnt;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, cnt * sizeof(unsigned int), ind, GL_STATIC_DRAW);

	}

	int* IndexBuffer::map() {
		return (int*) glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);
	}

	void IndexBuffer::unmap() {
	
		glUnmapBuffer(this->m_ID);
	
	}

	void IndexBuffer::bind() {

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID);

	}
}