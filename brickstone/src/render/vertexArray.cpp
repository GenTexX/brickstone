#include <bspch.h>
#include "VertexArray.h"

bs::VertexArray::VertexArray() {

	glGenVertexArrays(1, &(this->id));
	this->vbo = new VertexBuffer();
	this->bind();
	this->vbo->bind();

}

bs::VertexArray::~VertexArray() {

	glDeleteVertexArrays(1, &(this->id));

}

int bs::VertexArray::getCount() {
	return this->count;
}

void bs::VertexArray::setData(const float * pos, const int & size) {

	this->count = size;
	this->vbo->bind();
	this->vbo->setData(pos, size);

}

void bs::VertexArray::setVertexAttrib(const int & index, const int & layout, const int & vertexSize, const int & stride, const int & offset) {

	this->vbo->bind();
	this->vbo->setVertexAttrib(index, layout, vertexSize, stride, offset);

}

float * bs::VertexArray::map() {

	this->vbo->bind();
	this->buffer = this->vbo->map();
	return this->buffer;

}

void bs::VertexArray::unmap() {

	this->vbo->unmap();

}

void bs::VertexArray::bind() {

	glBindVertexArray(this->id);

}

void bs::VertexArray::unbind() {

	glBindVertexArray(0);

}

float & bs::VertexArray::operator[](const int & index) {

	return buffer[index];

}
