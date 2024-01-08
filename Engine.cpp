#include "Engine.h"

Engine::Engine() {
	window = 0;
}

Engine::~Engine() {
	glfwTerminate();
	window = 0;
}

void Engine::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(800, 800, "Sequence", NULL, NULL);
	if (!window) {
		printf("Could not init Window!\n");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	glViewport(0, 0, 800, 800);
}

//void openglTest() {
//	while (!)
//	{
//		// input
//		// -----
//		processInput(window);
//
//		// render
//		// ------
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		
//	}
//	
//	return;
//}

bool Engine::windowLogic() {
	bool shouldExit=!glfwWindowShouldClose(window);
	glfwSwapBuffers(window);
	glfwPollEvents();
	return shouldExit;
}

void Engine::gameLogic() {

}

void Engine::render() {

}