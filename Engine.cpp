#include "Engine.h"

void Engine::initShaders() {
	std::string workingPath = std::filesystem::current_path().string();
	std::string vShader = workingPath + "\\Shaders\\CardVertexShader.glsl";
	std::string fShader = workingPath + "\\Shaders\\CardFragmentShader.glsl";
	cardShader = Shader(vShader.c_str(), fShader.c_str());
	cardShaderProjectionLocation = glGetUniformLocation(cardShader.shaderProgram, "projection");
	cardShaderViewLocation = glGetUniformLocation(cardShader.shaderProgram, "view");
	cardShaderModelLocation = glGetUniformLocation(cardShader.shaderProgram, "model");
	cardShaderCurrentTimeLocation = glGetUniformLocation(cardShader.shaderProgram, "currentTime");
}

void Engine::initVertexData() {
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	cardDrawVertex toGPU[6];
	//toGPU[0].location = glm::vec3(-0.25, 0.5, 0);
	//toGPU[1].location = glm::vec3(0.25, 0.5, 0);
	//toGPU[2].location = glm::vec3(-0.25, -0.5, 0);
	//toGPU[3] = toGPU[2];
	//toGPU[4] = toGPU[1];
	//toGPU[5].location = glm::vec3(-0.25, -0.5, 0);
	toGPU[0].location = glm::vec3(-0.25, 0.5, 0);
	toGPU[1].location = glm::vec3(-0.25, -0.5, 0);
	toGPU[2].location = glm::vec3(0.25, -0.5, 0);

	toGPU[3].location = glm::vec3(0.25, -0.5, 0);
	toGPU[4].location = glm::vec3(0.25, 0.5, 0);
	toGPU[5].location = glm::vec3(-0.25, 0.5, 0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cardDrawVertex) * 6, toGPU, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cardDrawVertex), (void*)0);
	glEnableVertexAttribArray(0);
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

	playerCam = new Camera(glm::vec3(0, 0, 1), glm::vec3(0), 100);
	playerCam->onFrameStart(800.f / 800.f);
	playerCam->setLocation(glm::vec3(0, 0, 1));
	playerCam->lookAt(glm::vec3(0));
	projection = playerCam->getProjection();

	engineStartTime = getCurrentMillis();
	printf("Init time: %llums\n", getCurrentMillis() - startTime);
	return true;
}

void Engine::inputs() {
	int leftMouse = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (leftMouse == GLFW_PRESS) {
		//printf("MouseDown\n");
	}
}

bool Engine::windowLogic() {
	bool shouldExit = !glfwWindowShouldClose(window);
	glfwPollEvents();
	return shouldExit;
}

void Engine::gameLogic() {

}

void Engine::render() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.1, 1);
	glm::mat4 view = playerCam->getView();
	float* p = &projection[0][0];
	float* v = &view[0][0];
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, 0, 0));
	cardShader.use();
	glUniformMatrix4fv(cardShaderProjectionLocation, 1, GL_FALSE, p);
	glUniformMatrix4fv(cardShaderViewLocation, 1, GL_FALSE, v);
	glUniformMatrix4fv(cardShaderModelLocation, 1, GL_FALSE, &model[0][0]);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glfwSwapBuffers(window);
}