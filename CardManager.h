#pragma once
#include "CommonInc.h"
#include "Shader.h"
#include "Texture.h"

struct cardDrawVertexData {
	glm::vec3 location;
};

struct DecalDraw {
	glm::vec3 vertexLocation;
	glm::vec2 textureCoord;
};

/*
Want to impliment frame buffer picking on the cards so that I know which card that I have selected and what not
Will be useful for the board as well to determine where the player has selected to go
*/

struct CardDraw {
	MoveComponent moveComponent;
	Card c;
	glm::vec2 texCoordTopLeft;
	glm::vec2 texCoordSize;
};

//faceCoords is an array of 4 vec2's that will be the corresponding face texture coords in the texture png
//suitCoords is an array of 4 vec2's that will be the corresponding suit texture coords
//Will return false if the card is invalid
//Coords are defined top left, bottom left, bottom right, top right
static bool cardGetTexCoord(Card c, glm::vec2* faceCoords, glm::vec2* suitCoords) {
	if (!c.isValid())
		return false;
	switch (c.suit) {
	case Spades:
		suitCoords[0] = glm::vec2(0.0083333333333333, 0.7527777777777778);
		suitCoords[1] = glm::vec2(0.0083333333333333, 0.7138888888888889);
		suitCoords[2] = glm::vec2(0.0265625, 0.7138888888888889);
		suitCoords[3] = glm::vec2(0.0265625, 0.7527777777777778);
		break;
	case Hearts:
		suitCoords[0] = glm::vec2(0.0083333333333333, 0.825);
		suitCoords[1] = glm::vec2(0.0083333333333333, 0.78518518518518518518518518518519);
		suitCoords[2] = glm::vec2(0.02864583333333333333333333333333, 0.78518518518518518518518518518519);
		suitCoords[3] = glm::vec2(0.02864583333333333333333333333333, 0.825);
		break;
	case Clubs:
		suitCoords[0] = glm::vec2(0.0083333333333333, 0.8990740740740741);
		suitCoords[1] = glm::vec2(0.0083333333333333, 0.8601851851851852);
		suitCoords[2] = glm::vec2(0.0307291666666667, 0.8601851851851852);
		suitCoords[3] = glm::vec2(0.0307291666666667, 0.8990740740740741);
		break;
	case Diamonds:
		suitCoords[0] = glm::vec2(0.0083333333333333, 0.9722222222222222);
		suitCoords[1] = glm::vec2(0.0083333333333333, 0.9324074074074074);
		suitCoords[2] = glm::vec2(0.0255208333333333, 0.9324074074074074);
		suitCoords[3] = glm::vec2(0.0255208333333333, 0.9722222222222222);
		break;
	}
	return true;
}

class CardManager {
	u32 cardVAO;
	u32 cardVBO;
	u32 cardProjectionLocation;
	u32 cardViewLocation;
	u32 cardModelLocation;
	Shader cardShader;
	u32 decalVAO;
	u32 decalVBO;
	u32 decalProjectionLocation;
	u32 decalViewLocation;
	u32 decalModelLocation;
	Shader decalShader;
	Texture decalTexture;
public:
	CardManager();
	~CardManager();
	void initShaders();
	void initVertexData();
	void tick(u64 currentTime, u64 deltaTime);
	void draw(float* projection, float* view);
};