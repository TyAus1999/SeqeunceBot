#pragma once
#include "CommonInc.h"
#include "Shader.h"
#include "Camera.h"
#include "CardManager.h"
#include "ChipManager.h"
#include "Game.h"

class Engine {
	GLFWwindow* window;
	u64 engineStartTime;
	u64 currentTime;
	u64 deltaTime;
	Camera* playerCam;
	glm::mat4 projection;
	void initShaders();
	void initVertexData();

	Game game;
	CardManager cardManager;
	ChipManager chipManager;
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