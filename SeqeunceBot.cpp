#include "CommonInc.h"
#include "Engine.h"

void processInput(GLFWwindow* window) {
	int leftMouse = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (leftMouse == GLFW_PRESS) {
		printf("MouseDown\n");
	}
}



int main() {
	Engine e;
	e.init();
	u64 startTime = getCurrentMillis();
	while (e.windowLogic()) {
		e.inputs();
		e.gameLogic();
		e.render();
	}
	return 0;
	//openglTest();
	//return 0;
	//srand(time(NULL));
	//Game g(2, 2);
	//bool isGood;
	//do {
	//	isGood = g.tick();
	//	//system("pause");
	//} while (isGood);
	//return 0;
}