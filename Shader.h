#pragma once
#include "CommonInc.h"

class Shader {
	u32 vertexShader;
	u32 geometryShader;
	u32 fragmentShader;
	const char* readFromFile(const char* path);
	void compile(const char* shaderSource, u32 shader);
public:
	u32 shaderProgram;
	Shader();
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	Shader(const char* vertexShaderPath, const char* geometryShaderPath, const char* fragmentShaderPath);
	~Shader();
	void use();
};