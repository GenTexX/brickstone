#pragma once

#include <string>
#include <GL/glew.h>
#include "../stb_image/stb_image.h"
#include <logging/log.h>

namespace bs {

	class Texture {
	private:
		
		unsigned int id;
		unsigned int slot;
		std::string path;
		unsigned char* buffer;
		int width, height;
		int bpp;

	public:
		Texture(const std::string& path = "", const unsigned int& slot = 0);
		~Texture();

		void setSlot(const unsigned int& slot);

		unsigned int& getSlot();

		void loadTexture(const std::string& path = "", unsigned int slot = 0);

		void bind();
		void unbind();

	};

}
