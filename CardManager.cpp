#include "CardManager.h"

void CardManager::changeCardTextureCoordsSuit(int suit) {
	glBindBuffer(GL_ARRAY_BUFFER, decalVBO);
	DecalDraw* decalData = (DecalDraw*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	glm::vec2 faceCoords[4];
	glm::vec2 suitCoords[4];
	cardGetTexCoord(Card(suit, Ace), faceCoords, suitCoords);
	decalData[0].textureCoord = suitCoords[0];
	decalData[1].textureCoord = suitCoords[1];
	decalData[2].textureCoord = suitCoords[3];
	decalData[3].textureCoord = suitCoords[3];
	decalData[4].textureCoord = suitCoords[1];
	decalData[5].textureCoord = suitCoords[2];
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

void CardManager::changeCardTextureCoordsFace(int face) {
	glBindBuffer(GL_ARRAY_BUFFER, decalVBO);
	DecalDraw* decalData = (DecalDraw*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	glm::vec2 faceCoords[4];
	glm::vec2 suitCoords[4];
	cardGetTexCoord(Card(Spades, face), faceCoords, suitCoords);
	decalData[0].textureCoord = faceCoords[0];
	decalData[1].textureCoord = faceCoords[1];
	decalData[2].textureCoord = faceCoords[3];
	decalData[3].textureCoord = faceCoords[3];
	decalData[4].textureCoord = faceCoords[1];
	decalData[5].textureCoord = faceCoords[2];
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

CardManager::CardManager() {

}

CardManager::~CardManager() {
	u32 vaos[2];
	vaos[0] = cardVAO;
	vaos[1] = decalVAO;
	glDeleteVertexArrays(2, vaos);
	u32 vbos[2];
	vbos[0] = cardVBO;
	vbos[1] = decalVBO;
	glDeleteBuffers(2, vbos);
}

void CardManager::initShaders() {
	std::string workingPath = std::filesystem::current_path().string();
	std::string vShader = workingPath + "\\Shaders\\CardVertexShader.glsl";
	std::string fShader = workingPath + "\\Shaders\\CardFragmentShader.glsl";
	cardShader = Shader(vShader.c_str(), fShader.c_str());
	cardProjectionLocation = glGetUniformLocation(cardShader.shaderProgram, "projection");
	cardViewLocation = glGetUniformLocation(cardShader.shaderProgram, "view");
	cardModelLocation = glGetUniformLocation(cardShader.shaderProgram, "model");
	//cardShaderCurrentTimeLocation = glGetUniformLocation(cardShader.shaderProgram, "currentTime");

	vShader = workingPath + "\\Shaders\\DecalVertexShader.glsl";
	fShader = workingPath + "\\Shaders\\DecalFragmentShader.glsl";
	decalShader = Shader(vShader.c_str(), fShader.c_str());
	decalProjectionLocation = glGetUniformLocation(decalShader.shaderProgram, "projection");
	decalViewLocation = glGetUniformLocation(decalShader.shaderProgram, "view");
	decalModelLocation = glGetUniformLocation(decalShader.shaderProgram, "model");

	//Texture
	std::string texPath = workingPath + "\\ImageEdits\\Texture.png";
	decalTexture.init(texPath.c_str());
}

void CardManager::initVertexData() {
	//Card
	glGenBuffers(1, &cardVBO);
	glGenVertexArrays(1, &cardVAO);
	glBindVertexArray(cardVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cardVBO);
	cardDrawVertexData toGPU[6];
	toGPU[0].location = glm::vec3(-3, 6, 0);
	toGPU[1].location = glm::vec3(-3, -6, 0);
	toGPU[2].location = glm::vec3(3, -6, 0);

	toGPU[3].location = glm::vec3(3, -6, 0);
	toGPU[4].location = glm::vec3(3, 6, 0);
	toGPU[5].location = glm::vec3(-3, 6, 0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cardDrawVertexData) * 6, toGPU, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cardDrawVertexData), (void*)0);
	glEnableVertexAttribArray(0);

	//Card Decals
	//Like for the suit and face
	glGenBuffers(1, &decalVBO);
	glGenVertexArrays(1, &decalVAO);
	glBindVertexArray(decalVAO);
	glBindBuffer(GL_ARRAY_BUFFER, decalVBO);
	glm::vec2 suitCoords[4];
	glm::vec2 faceCoords[4];
	if (!cardGetTexCoord(Card(Diamonds, King), faceCoords, suitCoords)) {
		printf("Could not get texture coords!\n");
	}
	DecalDraw decalGPU[6];
	//Top Left
	decalGPU[0].vertexLocation = glm::vec3(-1, 1, 0);
	decalGPU[0].textureCoord = faceCoords[0];
	//Bottom Left
	decalGPU[1].vertexLocation = glm::vec3(-1, -1, 0);
	decalGPU[1].textureCoord = faceCoords[1];
	//Top Right
	decalGPU[2].vertexLocation = glm::vec3(1, 1, 0);
	decalGPU[2].textureCoord = faceCoords[3];

	//Top Right
	decalGPU[3].vertexLocation = glm::vec3(1, 1, 0);
	decalGPU[3].textureCoord = decalGPU[2].textureCoord;
	//Bottom Left
	decalGPU[4].vertexLocation = glm::vec3(-1, -1, 0);
	decalGPU[4].textureCoord = decalGPU[1].textureCoord;
	//Bottom Right
	decalGPU[5].vertexLocation = glm::vec3(1, -1, 0);
	decalGPU[5].textureCoord = faceCoords[2];

	//for (int i = 0; i < 6; i++)
	//	decalGPU[i].vertexLocation *= 10;

	glBufferData(GL_ARRAY_BUFFER, sizeof(DecalDraw) * 6, decalGPU, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DecalDraw), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(DecalDraw), (void*)sizeof(glm::vec3));
	glEnableVertexAttribArray(1);
}

void CardManager::tick(u64 currentTime, u64 deltaTime) {

}

void CardManager::draw(float* projection, float* view, u64 currentTime) {
	int amountCards = cardDraws.size();
	if (amountCards <= 0)
		return;
	glm::mat4* cardModels = new glm::mat4[amountCards];
	glm::vec3 topLeftSuitOffset(-5,0,0);
	glm::vec3 topLeftFaceOffset(5,0,0);
	for (int i = 0; i < amountCards; i++) {
		cardModels[i] = glm::mat4(1);
		glm::vec3 cardLoc = cardDraws[i].moveComponent.getLocation(currentTime);
		cardModels[i] = glm::translate(cardModels[i], cardLoc);
		glm::mat4 topLeftSuitDecal = glm::mat4(1);
		glm::mat4 topLeftFaceDecal = glm::mat4(1);
		topLeftSuitDecal = glm::translate(topLeftSuitDecal, cardLoc + topLeftSuitOffset);
		topLeftFaceDecal = glm::translate(topLeftFaceDecal, cardLoc + topLeftFaceOffset);
		changeCardTextureCoordsSuit(cardDraws[i].c.suit);
		decalShader.use();
		decalTexture.use(0);
		glUniformMatrix4fv(decalProjectionLocation, 1, GL_FALSE, projection);
		glUniformMatrix4fv(decalViewLocation, 1, GL_FALSE, view);
		glUniformMatrix4fv(decalModelLocation, 1, GL_FALSE, &topLeftSuitDecal[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		//changeCardTextureCoordsFace(cardDraws[i].c.face);
		//decalShader.use();
		//decalTexture.use(0);
		//glUniformMatrix4fv(decalProjectionLocation, 1, GL_FALSE, projection);
		//glUniformMatrix4fv(decalViewLocation, 1, GL_FALSE, view);
		//glUniformMatrix4fv(decalModelLocation, 1, GL_FALSE, &topLeftFaceDecal[0][0]);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	cardShader.use();
	glUniformMatrix4fv(cardProjectionLocation, 1, GL_FALSE, projection);
	glUniformMatrix4fv(cardViewLocation, 1, GL_FALSE, view);
	glBindVertexArray(cardVAO);
	for (int i = 0; i < amountCards; i++) {
		glm::mat4& cCard = cardModels[i];
		glUniformMatrix4fv(cardModelLocation, 1, GL_FALSE, &cCard[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	delete[] cardModels;
	//decalShader.use();
	//decalTexture.use(0);
	//glUniformMatrix4fv(decalProjectionLocation, 1, GL_FALSE, projection);
	//glUniformMatrix4fv(decalViewLocation, 1, GL_FALSE, view);
	//glm::mat4 decalModel = glm::mat4(1);
	//decalModel = glm::translate(decalModel, glm::vec3(0, 0, 0));
	//glUniformMatrix4fv(decalModelLocation, 1, GL_FALSE, &decalModel[0][0]);
	//glBindVertexArray(decalVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	//cardShader.use();
	//glUniformMatrix4fv(cardProjectionLocation, 1, GL_FALSE, projection);
	//glUniformMatrix4fv(cardViewLocation, 1, GL_FALSE, view);
	//glm::mat4 model = glm::mat4(1);
	//model = glm::translate(model, glm::vec3(0));
	//glUniformMatrix4fv(cardModelLocation, 1, GL_FALSE, &model[0][0]);
	//glBindVertexArray(cardVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
}

u64 CardManager::addCard(Card c, double speed) {
	CardDraw toAdd;
	toAdd.c = c;
	toAdd.moveComponent.movementSpeed = speed;
	cardDraws.push_back(toAdd);
	return cardDraws.size() - 1;
}

bool CardManager::moveCard(u64 index, glm::vec3 destination, u64 currentTime) {
	if (index >= cardDraws.size())
		return false;
	cardDraws[index].moveComponent.moveTo(destination, currentTime);
	return true;
}

void CardManager::removeAllCards() {
	cardDraws.clear();
}