#pragma once
#include "CommonInc.h"
#include "Shader.h"

struct ChipVertexData {
	glm::vec3 vertexLocation;
};

class ChipManager {
	u32 vao;
	u32 vbo;
	u32 projectionLocation;
	u32 viewLocation;
	u32 modelLocation;
	u32 centreLocation;
	Shader chipShader;
public:
	ChipManager();
	~ChipManager();
	void initShaders();
	void initVertexData();
	void tick(u64 currentTime, u64 deltaTime);
	void draw(float* projection, float* view);
};