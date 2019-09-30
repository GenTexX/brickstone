#pragma once

#include <string>
#include <GL/glew.h>
#include "../stb_image/stb_image.h"

namespace bs {

	class Texture {
	private:
		
		unsigned int id;
		std::string path;
		unsigned char* buffer;
		int width, height;
		int bpp;

	public:
		Texture(const std::string& path = "");
		~Texture();

		void bind(const int& slot = 0);
		void unbind();

	};

}
