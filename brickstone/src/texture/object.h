#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../file/FileHandler.h"
#include "../string/StringFormating.h"
#include "../render/VertexBuffer.h"
#include "../render/VertexArray.h"
#include "../render/IndexBuffer.h"
#include "../math/maths.h"

namespace bs {

	class Object {
	private:
	
	public:
		VertexArray vao;
		Object();
		~Object();

		void readFile(const std::string& path);

	};

}