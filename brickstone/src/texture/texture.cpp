#include <bspch.h>
#include "texture.h"

bs::Texture::Texture(const std::string & path) : path(path) {

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

bs::Texture::~Texture() {

	glDeleteTextures(1, &(this->id));

}

void bs::Texture::bind(const int& slot) {

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, this->id);

}

void bs::Texture::unbind() {

	glBindTexture(GL_TEXTURE_2D, 0);

}
