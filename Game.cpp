#include "Game.h"

Game::Game(int players, int teams) {
	initGame(players, teams);
}

Game::~Game() {
	if (players)
		delete[] players;
	if (aiPlayers)
		delete[] aiPlayers;
}

void Game::initPlayer(int player, int team, Card* hand, int amountInHand) {
	if (player < 0 || player >= amountPlayers)
		return;
	Player* p = &players[player];
	p->setCardsInHand(amountInHand);
	p->setHand(hand);
	p->team = team;
}

void Game::initGame(int players, int teams) {
	amountTeams = teams;
	amountPlayers = players;
	this->players = new Player[amountPlayers];
	aiPlayers = new bool[amountPlayers];
	currentPlayerTurn = 0;
	int setTeam = 0;
	for (int i = 0; i < amountPlayers; i++) {
		aiPlayers[i] = false;
		Player* p = &this->players[i];
		p->team = setTeam;
		if (setTeam >= teams - 1)
			setTeam = 0;
		else
			setTeam++;
	}
	aiPlayers[0] = true;
	aiPlayers[1] = true;
	//printf("What cards does the AI have\n");
	//Card* cards = getRealCards(8);
	//Card* cards = getSetCards();
	Card* cards = getValidRandomCards(8);
	this->players[0].setCardsInHand(8);
	this->players[0].setHand(cards);
	delete[] cards;
	printf("Player 0 Hand\n");
	this->players[0].printHand();

	//For the other ai player
	cards = getValidRandomCards(8);
	this->players[1].setCardsInHand(8);
	this->players[1].setHand(cards);
	delete[] cards;
	printf("Player 1 Hand\n");
	this->players[1].printHand();
}

void Game::setPlayerAI(int player) {
	if (player < 0 || player >= amountPlayers)
		return;
	aiPlayers[player] = true;
}

bool Game::tick() {
	//b.drawBoard();
	if (!b.hasValidPlaceToPlay()) {
		printf("No More Places To Play!\n");
		return false;
	}
	int winning;
	if (b.checkWin(&winning, 2, amountTeams)) {
		b.drawBoard();
		printf("Winning Team: %i\n", winning);
		return false;
	}
	Player* p = &players[currentPlayerTurn];
	printf("Player: %i\n", currentPlayerTurn);
	printf("\tTeam: %i\n", p->team);
	if (aiPlayers[currentPlayerTurn]) {
		printf("\tIs AI\nHand:\n");
		//AI function
		p->printHand();
		int x, y, cardIndex;
		if (!getAiBestLocation(currentPlayerTurn, &x, &y, &cardIndex)) {
			printf("AI wants to play an invalid location!, X: %i, Y: %i\n", x, y);
			return true;
		}
		if (!b.playPeice(x, y, p->team)) {
			printf("Location could not be played on the board\n");
			return true;
		}
		std::string faceName = getFaceName(p->hand[cardIndex].face);
		std::string suitName = getSuitName(p->hand[cardIndex].suit);
		printf("Ai Played %s, %s, at X: %i, Y: %i\n", faceName.c_str(), suitName.c_str(), x, y);
		b.drawBoard();
		Card pickedUp = getValidRandomPickup();
		printf("AI Picked up\n");
		pickedUp.print();
		p->hand[cardIndex] = pickedUp;
		//printf("Which card did Player %i pick up\n", currentPlayerTurn);
		//Card* pickedUp = getRealCards(1);
		//p->hand[cardIndex] = pickedUp[0];
		//delete[] pickedUp;
	}
	else {
		printf("\tIs Human\nInput:\n");
		int x, y;
		getHumanInput(&x, &y);
		if (!b.playPeice(x, y, p->team)) {
			printf("Location could not be played\n");
			return true;
		}
	}
	printf("=========================================================\n");
	currentPlayerTurn++;
	if (currentPlayerTurn >= amountPlayers)
		currentPlayerTurn = 0;
	return true;
}

void Game::getHumanInput(int* x, int* y) {
	printf("X: ");
	std::cin >> *x;
	printf("Y: ");
	std::cin >> *y;
}

Card* Game::getRealCards(int amount) {
	Card* out = new Card[amount];
	printf("Suits:\n");
	for (int i = 1; i <= Spades; i++)
		printf("%i: %s, ", i, getSuitName(i).c_str());
	printf("\nFaces:\n");
	for (int i = 1; i <= King; i++)
		printf("%i: %s, ", i, getFaceName(i).c_str());
	printf("\n");
	for (int i = 0; i < amount; i++) {
		bool isGood = true;
		while (1) {
			printf("Card: %i\n", i);
			int suit, face;
			printf("Suit: ");
			std::cin >> suit;
			if (suit > Spades || suit < Diamonds)
				isGood = false;
			printf("Face: ");
			std::cin >> face;
			if (face<1 || face>King)
				isGood = false;
			if (!isGood)
				printf("Card is invalid\n");
			out[i] = Card(suit, face);
			printf("==================\n");
			if (isGood)
				break;
		}
	}
	return out;
}

Card* Game::getSetCards() {
	Card* out = new Card[8];
	out[0] = Card(Spades, Queen);
	out[1] = Card(Spades, 10);
	out[2] = Card(Spades, King);
	out[3] = Card(Spades, Ace);
	out[4] = Card(Diamonds, 2);
	out[5] = Card(Diamonds, 3);
	out[6] = Card(Diamonds, 4);
	out[7] = Card(Diamonds, 5);
	return out;
}

Card* Game::getValidRandomCards(int amount) {
	Card* out = new Card[amount];
	for (int i = 0; i < amount; i++) {
		Card* cCard = &out[i];
		bool isGood = false;
		while (!isGood) {
			int inHand = 0;
			cCard->setRandom();
			for (int p = 0; p < amountPlayers; p++) {
				Player* cPlayer = &players[p];
				if (cPlayer->isInHand(cCard)) {
					if (inHand > 1)
						break;
					inHand++;
				}
			}
			//For checking if already in the hand to return
			for (int p = i - 1; p > -1; p--) {
				Card* testCard = &out[p];
				if (testCard->isEqual(cCard)) {
					if (inHand > 1)
						break;
					inHand++;
				}
			}
			if (inHand < 2)
				isGood = true;
		}
	}
	return out;
}

Card Game::getValidRandomPickup() {
	Card out;
	bool isGood = false;
	while (!isGood) {
		int amount = 0;
		out.setRandom();
		//Check the players
		for (int i = 0; i < amountPlayers; i++) {
			Player* cPlayer = &players[i];
			if (cPlayer->isInHand(&out)) {
				if (amount > 1)
					break;
				amount++;
			}
		}
		//Check the board for the card
		amount += b.amountPlayed(&out);
		if (amount < 2)
			isGood = true;
	}
	return out;
}

bool Game::getAiBestLocation(int player, int* x, int* y, int* cardIndex) {
	//Player* p = &players[player];
	//struct xy {
	//	int x;
	//	int y;
	//	int cardIndex;
	//};
	//std::vector<xy> validLocations;
	////Checking for jacks
	//int jack2EyeCardIndex = -1;
	//if (p->has2EyedJack(&jack2EyeCardIndex)) {
	//	for (int tx = 0; tx < 10; tx++) {
	//		for (int ty = 0; ty < 10; ty++) {
	//			Place* place = b.getPlace(tx, ty);
	//			if (place->isFree || place->teamOwned != -1)
	//				continue;
	//			xy toAdd;
	//			toAdd.x = tx;
	//			toAdd.y = ty;
	//			toAdd.cardIndex = jack2EyeCardIndex;
	//			validLocations.push_back(toAdd);
	//		}
	//	}
	//}
	////checking for single eye jacks
	//int jack1EyeCardIndex = -1;
	//if (p->has1EyedJack(&jack1EyeCardIndex)) {
	//	for (int tx = 0; tx < 10; tx++) {
	//		for (int ty = 0; ty < 10; ty++) {
	//			Place* place = b.getPlace(tx, ty);
	//			if (place->isFree || place->teamOwned == -1 || place->teamOwned == p->team)
	//				continue;

	//		}
	//	}
	//}
	////Checking for all of the cards that are in hand
	//for (int tY = 0; tY < 10; tY++) {
	//	for (int tX = 0; tX < 10; tX++) {
	//		Place* tempPlace = b.getPlace(tX, tY);
	//		if (tempPlace->teamOwned != -1)
	//			continue;
	//		int cardIndex;
	//		if (p->isInHand(&tempPlace->card, &cardIndex)) {
	//			xy toAdd;
	//			toAdd.x = tX;
	//			toAdd.y = tY;
	//			toAdd.cardIndex = cardIndex;
	//			validLocations.push_back(toAdd);
	//		}
	//	}
	//}
	//std::map<int, xy> weightedLocations;
	//for (int i = 0; i < validLocations.size(); i++) {
	//	std::pair<int, xy> toAdd;
	//	xy* loc = &validLocations[i];
	//	toAdd.first = b.weighPoint(p->team, loc->x, loc->y);
	//	printf("Weight: %i, X: %i, Y: %i, Team: %i\n", toAdd.first, loc->x, loc->y, p->team);
	//	toAdd.second = *loc;
	//	if (toAdd.first > -1)
	//		weightedLocations.insert(toAdd);
	//}
	//if (weightedLocations.empty())
	//	return false;
	//auto endMinus = std::prev(weightedLocations.end());
	//*x = endMinus->second.x;
	//*y = endMinus->second.y;
	//*cardIndex = endMinus->second.cardIndex;
	return true;
}