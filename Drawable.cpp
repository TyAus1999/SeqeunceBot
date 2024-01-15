#include "Drawable.h"

Drawable::Drawable(u32 drawType) {
	this->drawType = drawType;
	model = glm::mat4(1.f);
}

void Drawable::translate(glm::vec3 location) {
	this->location = location;
	model = glm::translate(model, location);
}

void Drawable::addMovement(glm::vec3 velocities, double deltaTime) {
	location += velocities * (float)deltaTime;
	model = glm::translate(model, location);
}

glm::vec3 Drawable::getLocation() {
	return location;
}

void Drawable::draw(u32 modelLocation) {
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
	switch (drawType) {
	case DrawableTypeCard:
		glDrawArrays(GL_TRIANGLES, 0, 6);
		break;
	}
}