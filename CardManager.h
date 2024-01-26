#pragma once
#include "CommonInc.h"
#include "Shader.h"

struct cardDrawVertexData {
	glm::vec3 location;
};

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