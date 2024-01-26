#include "Texture.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void Texture::saveImage(std::string name, int width, int height, void* data) {
	stbi_flip_vertically_on_write(true);
	if (!stbi_write_png(name.c_str(), width, height, 3, data, width * 3))
		printf("Save Image Failed\n");
}

Texture::Texture() {
	texture = 0;
}

Texture::~Texture() {
	//release();
}

void Texture::makeTexture(unsigned int* texLoc, const char* fp) {
	glGenTextures(1, texLoc);
	glBindTexture(GL_TEXTURE_2D, *texLoc);
	//Set the wrapping params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Set the filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Load the actual texture
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(fp, &width, &height, &nrChannel, 0);
	if (!data)
		printf("Failed to load texture: %s\n", fp);
	//printf("Channels: %i\n", nrChannel);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

void Texture::init(const char* textureLocation) {
	makeTexture(&texture, textureLocation);
}

void Texture::use(unsigned int textureSlot) {
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::release() {
	glDeleteTextures(1, &texture);
	texture = 0;
}

unsigned int Texture::getTexture() {
	return texture;
}