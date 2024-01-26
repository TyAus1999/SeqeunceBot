#pragma once
#include "CommonInc.h"
#include "Shader.h"
#include "Camera.h"
#include "Drawable.h"

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
	u64 currentTime;
	u64 deltaTime;
	Camera* playerCam;
	glm::mat4 projection;
	void initShaders();
	void initVertexData();

	Drawable testCard;
public:
	Engine();
	~Engine();
	//Used for getting time since app start
	u64 getTimeMillis();
	bool init();
	void inputs();
	bool windowLogic();
	void gameLogic();
	void render();
	void deltaTimeStart();
	void deltaTimeEnd();
};