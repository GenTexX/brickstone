#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <file/FileHandler.h>
#include <string/StringFormatting.h>
#include <render/VertexBuffer.h>
#include <render/VertexArray.h>
#include <render/IndexBuffer.h>
#include <math/maths.h>
#include <logging/log.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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