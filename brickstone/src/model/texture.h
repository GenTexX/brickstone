#pragma once

#include <string>
#include <GL/glew.h>
#include "../stb_image/stb_image.h"
#include <logging/log.h>

namespace bs {
	enum TextureType {
		DIFFUSE_MAP = 0,
		SPECULAR_MAP = 1,
		NORMAL_MAP = 2
	};
	class Texture {
	private:
		
		unsigned int id;
		unsigned int slot;
		TextureType type;
		std::string path;
		unsigned char* buffer;
		int width, height;
		int bpp;

	public:
		Texture(const std::string& path = "", const unsigned int& slot = 0);
		~Texture();

		void setSlot(const unsigned int& slot);
		void setType(TextureType type);

		unsigned int& getSlot();
		TextureType getType();

		void loadTexture(const std::string& path = "", unsigned int slot = 0);

		void bind();
		void unbind();

	};

}
