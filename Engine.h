#pragma once
#include "CommonInc.h"
#include "Shader.h"
#include "Camera.h"

struct cardDrawVertex {
	glm::vec3 location;
};

class Engine {
	GLFWwindow* window;
	u32 cardShaderProjectionLocation;
	u32 cardShaderViewLocation;
	u32 cardShaderModelLocation;
	u32 cardShaderCurrentTimeLocation;
	Shader cardShader;
	u32 vao;
	u32 vbo;
	u64 engineStartTime;
	Camera* playerCam;
	glm::mat4 projection;
	void initShaders();
	void initVertexData();
public:
	Engine();
	~Engine();
	u64 getTimeMillis();
	bool init();
	void inputs();
	bool windowLogic();
	void gameLogic();
	void render();
};