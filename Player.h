#pragma once
#include "Card.h"

class Player {
public:
	Card* hand;
	int cardsInHand;
	int team;
	Player(int maxCards = 8);
	~Player();
	void setHand(Card* cards);
	void setCardsInHand(int amount);
	bool isInHand(Card* c, int* cardIndex);
};