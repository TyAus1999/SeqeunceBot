#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, float fov, float near, float far) {
	this->position = position;
	this->target = target;
	direction = glm::normalize(this->position - this->target);
	up = glm::vec3(0.f, 1.f, 0.f);
	right = glm::normalize(glm::cross(up, direction));
	view = glm::lookAt(this->position, this->target, up);
	movementSpeed = 1.f;
	this->fov = fov;
	this->near = near;
	this->far = far;
	projection = glm::mat4(1.f);
	shiftDown = false;
}

void Camera::moveCameraNoTarget(cameraDirection d, double deltaTime) {
	glm::vec3 directionVec(0.f);
	switch (d) {
	case UP:
		directionVec = glm::vec3(0.f, 1.f, 0.f);
		break;
	case DOWN:
		directionVec = glm::vec3(0.f, -1.f, 0.f);
		break;
	case LEFT:
		directionVec = glm::vec3(-1.f, 0.f, 0.f);
		break;
	case RIGHT:
		directionVec = glm::vec3(1.f, 0.f, 0.f);
		break;
	case FORWARDS:
		directionVec = glm::vec3(0.f, 0.f, -1.f);
		break;
	case BACKWARDS:
		directionVec = glm::vec3(0.f, 0.f, 1.f);
		break;
	}
	float mSpeed = shiftDown ? movementSpeed * 5 : movementSpeed;
	glm::vec3 distanceMoved = directionVec * mSpeed * (float)deltaTime;
	distanceMoved *= position.z;
	position += distanceMoved;
	direction = glm::normalize(position - target);
	right = glm::normalize(glm::cross(up, direction));
	view = glm::lookAt(position, target, up);
}

void Camera::moveCamera(cameraDirection d, double deltaTime) {
	glm::vec3 directionVec(0.f);
	switch (d) {
	case UP:
		directionVec = glm::vec3(0.f, 1.f, 0.f);
		break;
	case DOWN:
		directionVec = glm::vec3(0.f, -1.f, 0.f);
		break;
	case LEFT:
		directionVec = glm::vec3(-1.f, 0.f, 0.f);
		break;
	case RIGHT:
		directionVec = glm::vec3(1.f, 0.f, 0.f);
		break;
	case FORWARDS:
		directionVec = glm::vec3(0.f, 1.f, 0.f);
		break;
	case BACKWARDS:
		directionVec = glm::vec3(0.f, -1.f, 0.f);
		break;
	}
	float mSpeed = shiftDown ? movementSpeed * 5 : movementSpeed;
	glm::vec3 distanceMoved = directionVec * mSpeed * (float)deltaTime;
	distanceMoved *= position.z;
	position += distanceMoved;
	target += distanceMoved;
	direction = glm::normalize(position - target);
	right = glm::normalize(glm::cross(up, direction));
	view = glm::lookAt(position, target, up);
}

void Camera::setShiftDown(bool isDown) {
	shiftDown = isDown;
}

void Camera::multiplySpeed(float m) {
	setSpeed(m * movementSpeed);
}

void Camera::setSpeed(float s) {
	movementSpeed = s;
}

float Camera::getSpeed() {
	return movementSpeed;
}

void Camera::lookAt(glm::vec3 target) {
	this->target = target;
	direction = glm::normalize(position - this->target);
	right = glm::normalize(glm::cross(up, direction));
	view = glm::lookAt(position, this->target, up);
}

void Camera::setLocation(glm::vec3 location) {
	position = location;
	direction = glm::normalize(position - target);
	right = glm::normalize(glm::cross(up, direction));
	view = glm::lookAt(position, target, up);
}

void Camera::onFrameStart(float ratio) {
	projection = glm::perspective(glm::radians(fov), ratio, near, far);
}

//Gets the ray from the camera towards the mouse in 3d space
glm::vec3 Camera::getUnitVecFromMouse(double normalizedX, double normalizedY) {
	glm::vec3 ray_nds((float)normalizedX, (float)normalizedY, 1.f);
	glm::vec4 ray_clip(ray_nds.x, ray_nds.y, -1, 1.0);
	glm::vec4 rayEye = glm::inverse(projection) * ray_clip;
	rayEye.z = -1;
	rayEye.w = 0;
	glm::vec3 rayWorld = (glm::inverse(view) * rayEye);
	rayWorld = glm::normalize(rayWorld);
	return rayWorld;
}

glm::mat4 Camera::getProjection() {
	return projection;
}

glm::mat4 Camera::getView() {
	return view;
}

glm::vec3 Camera::getDirection() {
	return direction;
}

glm::vec3 Camera::getPosition() {
	return position;
}

glm::vec3 Camera::getCameraUp() {
	return up;
}

glm::vec3 Camera::getLookAt() {
	return target;
}