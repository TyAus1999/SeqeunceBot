#include "Shader.h"

const char* Shader::readFromFile(const char* path) {
	FILE* fd;
	fopen_s(&fd, path, "r");
	if (!fd)
		return 0;
	std::vector<char> source;
	char ch = fgetc(fd);
	while (ch != EOF) {
		source.push_back(ch);
		ch = fgetc(fd);
	}
	fclose(fd);
	char* out = (char*)malloc(sizeof(char) * source.size() + 1);
	if (!out)
		return 0;
	for (u64 i = 0; i < source.size(); i++)
		out[i] = source[i];
	out[source.size()] = 0;
	return out;
}

void Shader::compile(const char* shaderSource, u32 shader) {
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("Could not compile shader: %s\n", infoLog);
		printf("\n\n%s\n\n", shaderSource);
	}
}

Shader::Shader() {
	vertexShader = 0;
	geometryShader = 0;
	fragmentShader = 0;
	shaderProgram = 0;
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	geometryShader = 0;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexSource = readFromFile(vertexShaderPath);
	compile(vertexSource, vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentSource = readFromFile(fragmentShaderPath);
	compile(fragmentSource, fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Could not link shaders together: %s\n", infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	free((void*)vertexSource);
	free((void*)fragmentSource);

}

Shader::Shader(const char* vertexShaderPath, const char* geometryShaderPath, const char* fragmentShaderPath) {
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexSource = readFromFile(vertexShaderPath);
	compile(vertexSource, vertexShader);
	geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	const char* geoSource = readFromFile(geometryShaderPath);
	compile(geoSource, geometryShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentSource = readFromFile(fragmentShaderPath);
	compile(fragmentSource, fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, geometryShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Could not link shaders together: %s\n", infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);
	free((void*)vertexSource);
	free((void*)geoSource);
	free((void*)fragmentSource);
}

Shader::~Shader() {

}

void Shader::use() {
	glUseProgram(shaderProgram);
}