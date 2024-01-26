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

struct MoveComponent {
	glm::vec3 startPos;
	glm::vec3 destination;
	glm::vec3 directionNormalized;
	u64 assignmentTime;
	u64 arrivalTime;
	double movementSpeed;
	MoveComponent(double movementSpeed = 20) {
		startPos = glm::vec3(0);
		destination = glm::vec3(0);
		directionNormalized = glm::vec3(0);
		assignmentTime = 0;
		arrivalTime = 0;
		this->movementSpeed = movementSpeed;
	}
	glm::vec3 getLocation(u64 currentTime) {
		if (currentTime > arrivalTime)
			return destination;
		u64 timeDiff = currentTime - assignmentTime;
		float distTravelled = (float)timeDiff * (movementSpeed / 1000.0);
		return startPos + (directionNormalized * distTravelled);
	}
	void moveTo(glm::vec3 target, u64 currentTime) {
		startPos = getLocation(currentTime);
		destination = target;
		assignmentTime = currentTime;
		double distance = glm::distance(startPos, target);
		double unitTime = distance / (movementSpeed / 1000.0);
		arrivalTime = currentTime + (u64)unitTime;
		directionNormalized = glm::normalize(target - startPos);
	}
};