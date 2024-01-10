#pragma once
#include "CommonInc.h"
#include "Shader.h"

class Engine {
	GLFWwindow* window;
	Shader cardShader;
	void initShaders();
public:
	Engine();
	~Engine();
	void init();
	void inputs();
	bool windowLogic();
	void gameLogic();
	void render();
};