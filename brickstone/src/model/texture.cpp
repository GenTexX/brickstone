#include <bspch.h>
#include "texture.h"

namespace bs {

	Texture::Texture(const std::string& path, const unsigned int& slot) : path(path), slot(slot) {

		stbi_set_flip_vertically_on_load(1);
		this->buffer = stbi_load(this->path.c_str(), &(this->width), &(this->height), &(bpp), 4);

		glGenTextures(1, &(this->id));
		glBindTexture(GL_TEXTURE_2D, this->id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)buffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (this->buffer)
			stbi_image_free(this->buffer);
	}

	Texture::~Texture() {

		glDeleteTextures(1, &(this->id));

	}

	void Texture::setSlot(const unsigned int& slot)	{
		this->slot = slot;
	}

	void Texture::setType(TextureType type) {
		this->type = type;
	}

	unsigned int& Texture::getSlot() {
		return this->slot;
	}

	TextureType Texture::getType()
	{
		return this->type;
	}

	void Texture::loadTexture(const std::string& path, unsigned int slot) {

		this->path = path;
		this->slot = slot;

		stbi_set_flip_vertically_on_load(1);
		this->buffer = stbi_load(this->path.c_str(), &(this->width), &(this->height), &(bpp), 4);

		glBindTexture(GL_TEXTURE_2D, this->id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)buffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (this->buffer)
			stbi_image_free(this->buffer);
	}

	void Texture::bind() {

		glActiveTexture(GL_TEXTURE0 + this->slot);
		glBindTexture(GL_TEXTURE_2D, this->id);

	}

	void Texture::unbind() {

		glBindTexture(GL_TEXTURE_2D, 0);

	}

}