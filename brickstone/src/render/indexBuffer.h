#pragma once

#include <GL/glew.h>


namespace bs {

	class IndexBuffer {
	private:
		unsigned int m_ID;
		int m_Count;

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