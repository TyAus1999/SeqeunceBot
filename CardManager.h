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