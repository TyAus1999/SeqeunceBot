#pragma once
#include "CommonInc.h"
#include "Shader.h"

struct cardDrawVertexData {
	glm::vec3 location;
};

/*
Want to impliment frame buffer picking on the cards so that I know which card that I have selected and what not
Will be useful for the board as well to determine where the player has selected to go
*/

class CardManager {
	u32 vao;
	u32 vbo;
	u32 projectionLocation;
	u32 viewLocation;
	u32 modelLocation;
	Shader cardShader;


public:
	CardManager();
	~CardManager();
	void initShaders();
	void initVertexData();
	void tick(u64 currentTime, u64 deltaTime);
	void draw(float* projection, float* view);
};