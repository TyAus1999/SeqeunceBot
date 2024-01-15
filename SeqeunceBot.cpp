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
	if (!e.init()) {
		printf("Could not init Engine!\n");
		return -1;
	}
	while (e.windowLogic()) {
		e.deltaTimeStart();
		e.inputs();
		e.gameLogic();
		e.render();
		e.deltaTimeEnd();
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