#pragma once
#include <iostream>
#include <chrono>
#include <filesystem>
#include "Game.h"
#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef unsigned long long u64;
typedef unsigned int u32;

static u64 getCurrentMillis() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

static void printVec3(glm::vec3 loc) {
	printf("X: %f, Y: %f, Z: %f\n", loc.x, loc.y, loc.z);
}