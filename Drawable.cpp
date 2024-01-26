#include "Drawable.h"

bool Drawable::isMoving(u64 currentTime, glm::vec3* currentLocation) {
	if (currentTime > arrivalTime) {
		*currentLocation = destination;
		return false;
	}
	u64 timeDiff = currentTime - assignmentTime;
	float distTravelled = (float)timeDiff * movementSpeed;
	*currentLocation = startPos + (directionNormalized * distTravelled);
	return true;
}

Drawable::Drawable(u32 drawType) {
	this->drawType = drawType;
	model = glm::mat4(1.f);
	startPos = glm::vec3(0);
	destination = glm::vec3(0);
	directionNormalized = glm::vec3(0);
	movementSpeed = 0.5;
	assignmentTime = 0;
	arrivalTime = 0;
}

void Drawable::tick(u64 currentTime, u64 deltaTime) {
	glm::vec3 currentLocation = getLocation(currentTime);
	//printVec3(currentLocation);
	model = glm::mat4(1);
	model = glm::translate(model, currentLocation);
}

void Drawable::moveTo(glm::vec3 location, u64 currentTime) {
	startPos = getLocation(currentTime);
	destination = location;
	assignmentTime = currentTime;
	double distance = glm::distance(startPos, location);
	double unitTime = distance / movementSpeed;
	arrivalTime = currentTime + (u64)(unitTime * 1000.0);
	directionNormalized = glm::normalize(location - startPos);
}

glm::vec3 Drawable::getLocation(u64 currentTime) {
	if (currentTime > arrivalTime)
		return destination;
	u64 timeDiff = currentTime - assignmentTime;
	float distTravelled = (float)timeDiff * movementSpeed;
	return startPos + (directionNormalized * distTravelled);
}

void Drawable::draw(u32 modelLocation, u64 currentTime) {
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
	switch (drawType) {
	case DrawableTypeCard:
		glDrawArrays(GL_TRIANGLES, 0, 6);
		break;
	}
}