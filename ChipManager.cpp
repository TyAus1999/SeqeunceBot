#include "ChipManager.h"

ChipManager::ChipManager() {

}

ChipManager::~ChipManager() {

}

void ChipManager::initShaders() {
	std::string workingPath = std::filesystem::current_path().string();
	std::string vShader = workingPath + "\\Shaders\\ChipVertexShader.glsl";
	std::string fShader = workingPath + "\\Shaders\\ChipFragmentShader.glsl";
	chipShader = Shader(vShader.c_str(), fShader.c_str());
	projectionLocation = glGetUniformLocation(chipShader.shaderProgram, "projection");
	viewLocation = glGetUniformLocation(chipShader.shaderProgram, "view");
	modelLocation = glGetUniformLocation(chipShader.shaderProgram, "model");
}

void ChipManager::initVertexData() {
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	ChipVertexData toGPU[6];
	toGPU[0].vertexLocation = glm::vec3(-3, 3, 0);
	toGPU[1].vertexLocation = glm::vec3(-3, -3, 0);
	toGPU[2].vertexLocation = glm::vec3(3, 3, 0);

	toGPU[3].vertexLocation = glm::vec3(3, 3, 0);
	toGPU[4].vertexLocation = glm::vec3(-3, -3, 0);
	toGPU[5].vertexLocation = glm::vec3(3, -3, 0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ChipVertexData) * 6, toGPU, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ChipVertexData), (void*)0);
	glEnableVertexAttribArray(0);
}

void ChipManager::tick(u64 currentTime, u64 deltaTime) {

}

void ChipManager::draw(float* projection, float* view) {
	chipShader.use();
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projection);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, view);
	glm::mat4 model = glm::mat4(1);
	glm::vec3 loc(-1, 0, 0);
	model = glm::translate(model, loc);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}