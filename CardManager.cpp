#include "CardManager.h"

CardManager::CardManager() {

}

CardManager::~CardManager() {

}

void CardManager::initShaders() {
	std::string workingPath = std::filesystem::current_path().string();
	std::string vShader = workingPath + "\\Shaders\\CardVertexShader.glsl";
	std::string fShader = workingPath + "\\Shaders\\CardFragmentShader.glsl";
	cardShader = Shader(vShader.c_str(), fShader.c_str());
	projectionLocation = glGetUniformLocation(cardShader.shaderProgram, "projection");
	viewLocation = glGetUniformLocation(cardShader.shaderProgram, "view");
	modelLocation = glGetUniformLocation(cardShader.shaderProgram, "model");
	//cardShaderCurrentTimeLocation = glGetUniformLocation(cardShader.shaderProgram, "currentTime");
}

void CardManager::initVertexData() {
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	cardDrawVertexData toGPU[6];
	//toGPU[0].location = glm::vec3(-0.25, 0.5, 0);
	//toGPU[1].location = glm::vec3(0.25, 0.5, 0);
	//toGPU[2].location = glm::vec3(-0.25, -0.5, 0);
	//toGPU[3] = toGPU[2];
	//toGPU[4] = toGPU[1];
	//toGPU[5].location = glm::vec3(-0.25, -0.5, 0);
	toGPU[0].location = glm::vec3(-0.3, 0.5, 0);
	toGPU[1].location = glm::vec3(-0.3, -0.5, 0);
	toGPU[2].location = glm::vec3(0.3, -0.5, 0);

	toGPU[3].location = glm::vec3(0.3, -0.5, 0);
	toGPU[4].location = glm::vec3(0.3, 0.5, 0);
	toGPU[5].location = glm::vec3(-0.3, 0.5, 0);
	for (int i = 0; i < 6; i++)
		toGPU[i].location *= 10;
	glBufferData(GL_ARRAY_BUFFER, sizeof(cardDrawVertexData) * 6, toGPU, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cardDrawVertexData), (void*)0);
	glEnableVertexAttribArray(0);
}

void CardManager::tick(u64 currentTime, u64 deltaTime) {

}

void CardManager::draw(float* projection, float* view) {
	cardShader.use();
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projection);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, view);
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(0));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}