#pragma once
#include "CommonInc.h"

enum cameraDirection {
	UP, DOWN, LEFT, RIGHT, FORWARDS, BACKWARDS
};

class Camera {
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 direction;
	glm::vec3 up;
	glm::vec3 right;
	glm::mat4 view;
	float movementSpeed;
	bool shiftDown;

	glm::mat4 projection;
	float fov, near, far;
public:
	Camera(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f), glm::vec3 target = glm::vec3(0.f, 0.f, -1.f), float fov = 90.f, float near = 0.01f, float far = 5000.f);
	void moveCameraNoTarget(cameraDirection d, double deltaTime);
	void moveCamera(cameraDirection d, double deltaTime);
	void setShiftDown(bool isDown);
	void multiplySpeed(float m);
	void setSpeed(float s);
	float getSpeed();
	void lookAt(glm::vec3 target);
	void setLocation(glm::vec3 location);
	void onFrameStart(float ratio);
	glm::vec3 getUnitVecFromMouse(double normalizedX, double normalizedY);
	glm::mat4 getProjection();
	glm::mat4 getView();
	glm::vec3 getDirection();
	glm::vec3 getPosition();
	glm::vec3 getCameraUp();
	glm::vec3 getLookAt();
};