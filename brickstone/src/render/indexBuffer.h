#pragma once

#include <GL/glew.h>


namespace bs {

	class IndexBuffer {
	private:
		unsigned int id;
		int count;

	public:
		IndexBuffer();
		~IndexBuffer();

		int getCount();
		void setIndices(unsigned int *ind, const int& cnt);
		int* map();
		void unmap();
		void bind();

	};

}