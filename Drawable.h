#pragma once
#include "CommonInc.h"

enum DrawableType {
	DrawableTypeCard,
	DrawableTypeLast
};

class Drawable {
	u32 drawType;
	glm::mat4 model;
	glm::vec3 startPos;
	glm::vec3 destination;
	glm::vec3 directionNormalized;
	u64 assignmentTime;
	u64 arrivalTime;
	double movementSpeed;
	bool isMoving(u64 currentTime, glm::vec3* currentLocation);
public:
	Drawable(u32 drawType=DrawableTypeLast);
	void tick(u64 currentTime, u64 deltaTime);
	void moveTo(glm::vec3 location, u64 currentTime);
	glm::vec3 getLocation(u64 currentTime);
	void draw(u32 modelLocation, u64 currentTime);
};