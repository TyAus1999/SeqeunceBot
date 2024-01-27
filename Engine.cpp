#include "Engine.h"

void Engine::initShaders() {
	cardManager.initShaders();
	chipManager.initShaders();
}

void Engine::initVertexData() {
	cardManager.initVertexData();
	chipManager.initVertexData();
}

Engine::Engine() {
	window = 0;
}

Engine::~Engine() {
	glfwTerminate();
	window = 0;
	if (playerCam)
		delete[] playerCam;
}

u64 Engine::getTimeMillis() {
	return getCurrentMillis() - engineStartTime;
}

bool Engine::init() {
	u64 startTime = getCurrentMillis();
	printf("Initializing: @%llums\n", startTime);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(800, 800, "Sequence", NULL, NULL);
	if (!window) {
		printf("Could not init Window!\n");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	glViewport(0, 0, 800, 800);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	initShaders();
	initVertexData();

	playerCam = new Camera(glm::vec3(0, 0, 50), glm::vec3(0));
	playerCam->onFrameStart(800.f / 800.f);
	projection = playerCam->getProjection();

	u64 c = cardManager.addCard(Card(Spades, Queen));

	engineStartTime = getCurrentMillis();
	printf("Init time: %llums\n", getCurrentMillis() - startTime);

	return true;
}

void Engine::inputs() {
	static bool shouldSpawn = false;
	int leftMouse = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (leftMouse == GLFW_PRESS && shouldSpawn == false) {
		//printf("MouseDown\n");
		//testCard.addMovement(glm::vec3(0.001, 0, 0), deltaTime);
		shouldSpawn = true;
		u64 c = chipManager.addChip(glm::vec3(0, 0.5, 0.5));
		int rX, rY;
		rX = rand() % 100;
		rX -= 50;
		rY = rand() % 100;
		rY -= 50;
		chipManager.moveChip(c, glm::vec3(rX, rY, 0), currentTime);
		//printf("Chips: %llu\n", c);
	}
	else if (leftMouse == GLFW_RELEASE) {
		shouldSpawn = false;
	}
}

bool Engine::windowLogic() {
	bool shouldExit = !glfwWindowShouldClose(window);
	glfwPollEvents();
	return shouldExit;
}

void Engine::gameLogic() {
	cardManager.tick(currentTime, deltaTime);
	chipManager.tick(currentTime, deltaTime);
}

void Engine::render() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.1, 1);
	glm::mat4 view = playerCam->getView();
	float* p = &projection[0][0];
	float* v = &view[0][0];
	/*glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, 0, 0));*/
	//cardShader.use();
	//glUniformMatrix4fv(cardShaderProjectionLocation, 1, GL_FALSE, p);
	//glUniformMatrix4fv(cardShaderViewLocation, 1, GL_FALSE, v);
	////glUniformMatrix4fv(cardShaderModelLocation, 1, GL_FALSE, &model[0][0]);
	//glBindVertexArray(vao);
	////glDrawArrays(GL_TRIANGLES, 0, 6);
	chipManager.draw(p, v, currentTime);
	cardManager.draw(p, v, currentTime);


	glfwSwapBuffers(window);
}

void Engine::deltaTimeStart() {
	currentTime = getTimeMillis();
}

void Engine::deltaTimeEnd() {
	u64 cycleTime = getTimeMillis() - currentTime;
	if (cycleTime < 6) {
		u64 delayTime = 6 - cycleTime;
		std::this_thread::sleep_for(std::chrono::milliseconds(delayTime));
	}
	deltaTime = getTimeMillis() - currentTime;
	//printf("DeltaTime: %llu\n", deltaTime);
}