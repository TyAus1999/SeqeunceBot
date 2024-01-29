#include "CardManager.h"

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
	std::string gShader = workingPath + "\\Shaders\\DecalGeoShader.glsl";
	decalShader = Shader(vShader.c_str(), gShader.c_str(), fShader.c_str());
	decalProjectionLocation = glGetUniformLocation(decalShader.shaderProgram, "projection");
	decalViewLocation = glGetUniformLocation(decalShader.shaderProgram, "view");

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
	DecalDraw decalGPU;
	glm::vec2 suitCoords[4];
	glm::vec2 faceCoords[4];
	cardGetTexCoord(Card(Diamonds, King), faceCoords, suitCoords);
	decalGPU.decalOffset = glm::vec3(0, 5, 0);
	decalGPU.textureTopLeft = faceCoords[0];
	decalGPU.textureSize = faceCoords[2] - faceCoords[0];
	decalGPU.model = glm::translate(glm::mat4(1), glm::vec3(0));
	glBufferData(GL_ARRAY_BUFFER, sizeof(DecalDraw), &decalGPU, GL_DYNAMIC_DRAW);
	u64 offset = 0;
	//glm::vec3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DecalDraw), (void*)offset);
	glEnableVertexAttribArray(0);
	offset += sizeof(glm::vec3);
	//glm::vec2
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(DecalDraw), (void*)offset);
	glEnableVertexAttribArray(1);
	offset += sizeof(glm::vec2);
	//glm::vec2
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(DecalDraw), (void*)offset);
	glEnableVertexAttribArray(2);
	offset += sizeof(glm::vec2);
	//glm::mat4
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(DecalDraw), (void*)offset);
	glEnableVertexAttribArray(3);
	offset += sizeof(glm::vec4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(DecalDraw), (void*)offset);
	glEnableVertexAttribArray(4);
	offset += sizeof(glm::vec4);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(DecalDraw), (void*)offset);
	glEnableVertexAttribArray(5);
	offset += sizeof(glm::vec4);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(DecalDraw), (void*)offset);
	glEnableVertexAttribArray(6);
	offset += sizeof(glm::vec4);

	glVertexAttribIPointer(7, 1, GL_INT, sizeof(DecalDraw), (void*)offset);
	glEnableVertexAttribArray(7);
	offset += sizeof(int);

	//glm::vec2 suitCoords[4];
	//glm::vec2 faceCoords[4];
	//if (!cardGetTexCoord(Card(Diamonds, King), faceCoords, suitCoords)) {
	//	printf("Could not get texture coords!\n");
	//}
	//DecalDraw decalGPU[6];
	////Top Left
	//decalGPU[0].vertexLocation = glm::vec3(-1, 1, 0);
	//decalGPU[0].textureCoord = faceCoords[0];
	////Bottom Left
	//decalGPU[1].vertexLocation = glm::vec3(-1, -1, 0);
	//decalGPU[1].textureCoord = faceCoords[1];
	////Top Right
	//decalGPU[2].vertexLocation = glm::vec3(1, 1, 0);
	//decalGPU[2].textureCoord = faceCoords[3];

	////Top Right
	//decalGPU[3].vertexLocation = glm::vec3(1, 1, 0);
	//decalGPU[3].textureCoord = decalGPU[2].textureCoord;
	////Bottom Left
	//decalGPU[4].vertexLocation = glm::vec3(-1, -1, 0);
	//decalGPU[4].textureCoord = decalGPU[1].textureCoord;
	////Bottom Right
	//decalGPU[5].vertexLocation = glm::vec3(1, -1, 0);
	//decalGPU[5].textureCoord = faceCoords[2];

	////for (int i = 0; i < 6; i++)
	////	decalGPU[i].vertexLocation *= 10;

	//glBufferData(GL_ARRAY_BUFFER, sizeof(DecalDraw) * 6, decalGPU, GL_DYNAMIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DecalDraw), (void*)0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(DecalDraw), (void*)sizeof(glm::vec3));
	//glEnableVertexAttribArray(1);
}

void CardManager::tick(u64 currentTime, u64 deltaTime) {
	int amountCards = cardDraws.size();
	if (amountCards > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, decalVBO);
		DecalDraw* inGPU = (DecalDraw*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
		for (int i = 0; i < amountCards; i++) {
			//if (!cardDraws[i].moveComponent.isMoving(currentTime))
				//continue;
			int gpuOffset = i * 2;
			glm::vec3 cardLocation = cardDraws[i].moveComponent.getLocation(currentTime);
			glm::mat4 cardModel = glm::translate(glm::mat4(1), cardLocation);
			DecalDraw* face = &inGPU[gpuOffset];
			DecalDraw* suit = &inGPU[gpuOffset + 1];
			face->model = cardModel;
			suit->model = cardModel;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
}

void CardManager::draw(float* projection, float* view, u64 currentTime) {
	int amountCards = cardDraws.size();
	if (amountCards <= 0)
		return;
	//glm::mat4* cardModels = new glm::mat4[amountCards];
	//glm::vec3 topLeftSuitOffset(-5,0,0);
	//glm::vec3 topLeftFaceOffset(5,0,0);
	//for (int i = 0; i < amountCards; i++) {//I probably have to figure out a new way to render the suits and faces, this way is kinda stupid
	//	cardModels[i] = glm::mat4(1);
	//	glm::vec3 cardLoc = cardDraws[i].moveComponent.getLocation(currentTime);
	//	cardModels[i] = glm::translate(cardModels[i], cardLoc);
	//	glm::mat4 topLeftSuitDecal = glm::mat4(1);
	//	glm::mat4 topLeftFaceDecal = glm::mat4(1);
	//	topLeftSuitDecal = glm::translate(topLeftSuitDecal, cardLoc + topLeftSuitOffset);
	//	topLeftFaceDecal = glm::translate(topLeftFaceDecal, cardLoc + topLeftFaceOffset);
	//	changeCardTextureCoordsSuit(cardDraws[i].c.suit);
	//	decalShader.use();
	//	decalTexture.use(0);
	//	glUniformMatrix4fv(decalProjectionLocation, 1, GL_FALSE, projection);
	//	glUniformMatrix4fv(decalViewLocation, 1, GL_FALSE, view);
	//	glUniformMatrix4fv(decalModelLocation, 1, GL_FALSE, &topLeftSuitDecal[0][0]);
	//	glDrawArrays(GL_TRIANGLES, 0, 6);
	//	
	//	//changeCardTextureCoordsFace(cardDraws[i].c.face);
	//	//decalShader.use();
	//	//decalTexture.use(0);
	//	//glUniformMatrix4fv(decalProjectionLocation, 1, GL_FALSE, projection);
	//	//glUniformMatrix4fv(decalViewLocation, 1, GL_FALSE, view);
	//	//glUniformMatrix4fv(decalModelLocation, 1, GL_FALSE, &topLeftFaceDecal[0][0]);
	//	//glDrawArrays(GL_TRIANGLES, 0, 6);
	//}

	decalShader.use();
	glUniformMatrix4fv(decalProjectionLocation, 1, GL_FALSE, projection);
	glUniformMatrix4fv(decalViewLocation, 1, GL_FALSE, view);
	glBindVertexArray(decalVAO);
	glDrawArrays(GL_POINTS, 0, cardDraws.size() * 2);


	cardShader.use();
	glUniformMatrix4fv(cardProjectionLocation, 1, GL_FALSE, projection);
	glUniformMatrix4fv(cardViewLocation, 1, GL_FALSE, view);
	glBindVertexArray(cardVAO);
	for (int i = 0; i < amountCards; i++) {
		glm::mat4 cCard = glm::mat4(1);
		cCard = glm::translate(cCard, cardDraws[i].moveComponent.getLocation(currentTime));
		glUniformMatrix4fv(cardModelLocation, 1, GL_FALSE, &cCard[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
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

u64 CardManager::addCard(u64 currentTime, Card c, double speed) {
	CardDraw toAdd;
	toAdd.c = c;
	toAdd.moveComponent.movementSpeed = speed;
	cardDraws.push_back(toAdd);
	int amountCards = cardDraws.size();
	glBindBuffer(GL_ARRAY_BUFFER, decalVBO);
	DecalDraw* toGPU = new DecalDraw[amountCards * 2];
	for (int i = 0; i < amountCards; i++) {
		int gpuOffset = i * 2;
		glm::vec3 cardLocation = cardDraws[i].moveComponent.getLocation(currentTime);
		glm::vec2 suitCoords[4];
		glm::vec2 faceCoords[4];
		cardGetTexCoord(cardDraws[i].c, faceCoords, suitCoords);
		//First is the Face which is top left
		DecalDraw* face = &toGPU[gpuOffset];
		face->decalOffset = glm::vec3(-1.75, 4.75, 0);
		face->model = glm::translate(glm::mat4(1), cardLocation);
		face->textureTopLeft = faceCoords[0];
		face->textureSize = faceCoords[2] - faceCoords[0];
		//Second is the Suit which is top left but under the face
		DecalDraw* suit = &toGPU[gpuOffset + 1];
		suit->decalOffset = glm::vec3(-1.75, 2.5, 0);
		suit->model = glm::translate(glm::mat4(1), cardLocation);
		suit->textureTopLeft = suitCoords[0];
		suit->textureSize = suitCoords[2] - suitCoords[0];

		if (cardDraws[i].c.suit == Hearts || cardDraws[i].c.suit == Diamonds) {
			face->isRedSuit = 1;
			suit->isRedSuit = 1;
		}
		else {
			face->isRedSuit = 0;
			suit->isRedSuit = 0;
		}
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(DecalDraw) * amountCards * 2, toGPU, GL_DYNAMIC_DRAW);
	delete[] toGPU;
	return amountCards - 1;
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