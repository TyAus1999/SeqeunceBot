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
	centreLocation = glGetUniformLocation(chipShader.shaderProgram, "centreLocation");
}

void ChipManager::initVertexData() {
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	ChipVertexData toGPU[6];

}