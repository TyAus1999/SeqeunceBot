#pragma once
#include "CommonInc.h"

enum DrawableType {
	DrawableTypeCard,
	DrawableTypeLast
};

class Drawable {
	u32 drawType;
	glm::mat4 model;
	glm::vec3 location;
public:
	Drawable(u32 drawType=DrawableTypeLast);
	void translate(glm::vec3 location);
	void addMovement(glm::vec3 velocities, double deltaTime);
	glm::vec3 getLocation();
	void draw(u32 modelLocation);
};