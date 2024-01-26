#pragma once
#include "CommonInc.h"

enum DrawableType {
	DrawableTypeCard,
	DrawableTypeLast
};

class Drawable {
	u32 drawType;
	//Movement Stuff
	glm::vec3 startPos;
	glm::vec3 destination;
	glm::vec3 directionNormalized;
	u64 assignmentTime;
	u64 arrivalTime;
	double movementSpeed;
	std::vector<glm::vec3> moveWaypoints;
	//End Movement Stuff

	bool isMoving(u64 currentTime, glm::vec3* currentLocation);
	void calculateMoveTo(glm::vec3 location, u64 currentTime);
protected:
	glm::mat4 model;
public:
	Drawable(u32 drawType = DrawableTypeLast);
	void tick(u64 currentTime, u64 deltaTime);
	void moveTo(glm::vec3 location, u64 currentTime, bool addWaypoint = true);
	glm::vec3 getLocation(u64 currentTime);
	void setSpeed(double speed);
	double getSpeed();
	void draw(u32 modelLocation, u64 currentTime);
};