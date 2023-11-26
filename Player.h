#pragma once
#include "Card.h"

class Player {
public:
	Card* hand;
	int cardsInHand;
	int team;
	Player(int maxCards = 8);
	~Player();
	//Copies what was passed in
	//Will have to delete after passing into the function
	void setHand(Card* cards);
	void setCardsInHand(int amount);
	bool isInHand(Card* c, int* cardIndex = 0);
	bool has2EyedJack(int* cardIndex);
	bool has1EyedJack(int* cardIndex);
	void printHand();
};