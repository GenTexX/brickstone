#include <bspch.h>
#include "IndexBuffer.h"

namespace bs {

	IndexBuffer::IndexBuffer() {

		glGenBuffers(1, &(this->id));

	}

	IndexBuffer::~IndexBuffer() {

	}

	int IndexBuffer::getCount() {
		return this->count;
	}

	void IndexBuffer::setIndices(const unsigned int* ind, const int& cnt) {

		this->count = cnt;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, cnt * sizeof(unsigned int), ind, GL_STATIC_DRAW);

	}

	int* IndexBuffer::map() {
		return (int*) glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);
	}

	void IndexBuffer::unmap() {
	
		glUnmapBuffer(this->id);
	
	}

	void IndexBuffer::bind() {

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);

	}
}