#pragma once
#include "CommonInc.h"
class Texture {
protected:
	unsigned int texture;//Refers to the texture index in gpu
	void makeTexture(unsigned int* texLoc, const char* fp);
public:
	Texture();
	~Texture();
	unsigned int getTexture();
	void init(const char* textureLocation);
	void use(unsigned int textureSlot);
	void release();
	void saveImage(std::string name, int width, int height, void* data);

	/*Texture& operator=(Texture& other) {
		other.texture = 0;
	}
	Texture(Texture& other) : texture(other.texture) {
		if (this != &other) {
			release();
			std::swap(texture, other.texture);
		}
	}*/
};
