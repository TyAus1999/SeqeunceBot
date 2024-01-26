#pragma once
#include "CommonInc.h"
#include "Shader.h"

struct ChipVertexData {
	glm::vec3 vertexLocation;
};

struct Chip {
	MoveComponent moveComponent;
	glm::vec3 colour;
};

class ChipManager {
	u32 vao;
	u32 vbo;
	u32 projectionLocation;
	u32 viewLocation;
	u32 modelLocation;
	u32 chipColourLocation;
	Shader chipShader;
	std::vector<Chip> chips;
public:
	ChipManager();
	~ChipManager();
	void initShaders();
	void initVertexData();
	void tick(u64 currentTime, u64 deltaTime);
	void draw(float* projection, float* view, u64 currentTime);

	u64 addChip(glm::vec3 colour, double speed = 20);
	bool moveChip(u64 index, glm::vec3 destination, u64 currentTime);
	void removeAllChips();
};