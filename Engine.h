#pragma once
#include "CommonInc.h"

class Engine {
	GLFWwindow* window;
public:
	Engine();
	~Engine();
	void init();
	bool windowLogic();
	void gameLogic();
	void render();
};