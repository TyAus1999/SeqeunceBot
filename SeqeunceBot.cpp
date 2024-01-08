#include "CommonInc.h"

void openglTest() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window= glfwCreateWindow(800, 800, "Sequence", NULL, NULL);
	if (!window) {
		printf("Could not init Window!\n");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		//processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return;
}

int main() {
	srand(time(NULL));
	Game g(2, 2);
	bool isGood;
	do {
		isGood = g.tick();
		//system("pause");
	} while (isGood);
	return 0;
}