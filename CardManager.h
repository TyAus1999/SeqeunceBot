#pragma once
#include "CommonInc.h"
#include "Shader.h"
#include "Texture.h"

struct cardDrawVertexData {
	glm::vec3 location;
};

struct DecalDraw {
	//Offset of where the decal is based on the card
	glm::vec3 decalOffset;
	glm::vec2 textureTopLeft;
	glm::vec2 textureSize;
	//Card model
	glm::mat4 model;
};

/*
Want to impliment frame buffer picking on the cards so that I know which card that I have selected and what not
Will be useful for the board as well to determine where the player has selected to go
*/

struct CardDraw {
	MoveComponent moveComponent;
	Card c;
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
	switch (c.face) {
	case Ace:
		faceCoords[0] = glm::vec2(0.0307291666666667, 0.9777777777777778);
		faceCoords[1] = glm::vec2(0.0307291666666667, 0.9333333333333333);
		faceCoords[2] = glm::vec2(0.0567708333333333, 0.9333333333333333);
		faceCoords[3] = glm::vec2(0.0567708333333333, 0.9777777777777778);
		break;
	case 2:
		faceCoords[0] = glm::vec2(0.03125, 0.9046296296296296);
		faceCoords[1] = glm::vec2(0.03125, 0.8601851851851852);
		faceCoords[2] = glm::vec2(0.0479166666666667, 0.8601851851851852);
		faceCoords[3] = glm::vec2(0.0479166666666667, 0.9046296296296296);
		break;
	case 3:
		faceCoords[0] = glm::vec2(0.0322916666666667, 0.8314814814814815);
		faceCoords[1] = glm::vec2(0.0322916666666667, 0.7851851851851852);
		faceCoords[2] = glm::vec2(0.046875, 0.7851851851851852);
		faceCoords[3] = glm::vec2(0.046875, 0.8314814814814815);
		break;
	case 4:
		faceCoords[0] = glm::vec2(0.03125, 0.7583333333333333);
		faceCoords[1] = glm::vec2(0.03125, 0.712962962962963);
		faceCoords[2] = glm::vec2(0.0484375, 0.712962962962963);
		faceCoords[3] = glm::vec2(0.0484375, 0.7583333333333333);
		break;
	case 5:
		faceCoords[0] = glm::vec2(0.0322916666666667, 0.6842592592592593);
		faceCoords[1] = glm::vec2(0.0322916666666667, 0.6388888888888889);
		faceCoords[2] = glm::vec2(0.046875, 0.6388888888888889);
		faceCoords[3] = glm::vec2(0.046875, 0.6842592592592593);
		break;
	case 6:
		faceCoords[0] = glm::vec2(0.0322916666666667, 0.612037037037037);
		faceCoords[1] = glm::vec2(0.0322916666666667, 0.5657407407407407);
		faceCoords[2] = glm::vec2(0.0479166666666667, 0.5657407407407407);
		faceCoords[3] = glm::vec2(0.0479166666666667, 0.612037037037037);
		break;
	case 7:
		faceCoords[0] = glm::vec2(0.0322916666666667, 0.537962962962963);
		faceCoords[1] = glm::vec2(0.0322916666666667, 0.4925925925925926);
		faceCoords[2] = glm::vec2(0.0479166666666667, 0.4925925925925926);
		faceCoords[3] = glm::vec2(0.0479166666666667, 0.537962962962963);
		break;
	case 8:
		faceCoords[0] = glm::vec2(0.0328125, 0.4657407407407407);
		faceCoords[1] = glm::vec2(0.0328125, 0.4194444444444444);
		faceCoords[2] = glm::vec2(0.0473958333333333, 0.4194444444444444);
		faceCoords[3] = glm::vec2(0.0473958333333333, 0.4657407407407407);
		break;
	case 9:
		faceCoords[0] = glm::vec2(0.0322916666666667, 0.3925925925925926);
		faceCoords[1] = glm::vec2(0.0322916666666667, 0.3462962962962963);
		faceCoords[2] = glm::vec2(0.0479166666666667, 0.3462962962962963);
		faceCoords[3] = glm::vec2(0.0479166666666667, 0.3925925925925926);
		break;
	case Jack:
		faceCoords[0] = glm::vec2(0.03125, 0.3185185185185185);
		faceCoords[1] = glm::vec2(0.03125, 0.2731481481481481);
		faceCoords[2] = glm::vec2(0.0453125, 0.2731481481481481);
		faceCoords[3] = glm::vec2(0.0453125, 0.3185185185185185);
		break;
	case Queen:
		faceCoords[0] = glm::vec2(0.0317708333333333, 0.2462962962962963);
		faceCoords[1] = glm::vec2(0.0317708333333333, 0.187962962962963);
		faceCoords[2] = glm::vec2(0.05625, 0.187962962962963);
		faceCoords[3] = glm::vec2(0.05625, 0.2462962962962963);
		break;
	case King:
		faceCoords[0] = glm::vec2(0.03125, 0.1722222222222222);
		faceCoords[1] = glm::vec2(0.03125, 0.1277777777777778);
		faceCoords[2] = glm::vec2(0.0578125, 0.1277777777777778);
		faceCoords[3] = glm::vec2(0.0578125, 0.1722222222222222);
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
	Shader decalShader;
	Texture decalTexture;

	std::vector<CardDraw> cardDraws;

	void changeCardTextureCoordsSuit(int suit);
	void changeCardTextureCoordsFace(int face);
public:
	CardManager();
	~CardManager();
	void initShaders();
	void initVertexData();
	void tick(u64 currentTime, u64 deltaTime);
	void draw(float* projection, float* view, u64 currentTime);

	u64 addCard(Card c, double speed = 20);
	bool moveCard(u64 index, glm::vec3 destination, u64 currentTime);
	void removeAllCards();
};