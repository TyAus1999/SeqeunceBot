#include "Player.h"

Player::Player(int maxCards) {
	cardsInHand = maxCards;
	hand = new Card[cardsInHand];
}

Player::~Player() {
	if (hand)
		delete[] hand;
}

void Player::setHand(Card* cards) {
	if (!hand)
		return;
	memcpy(hand, cards, sizeof(Card) * cardsInHand);
}

void Player::setCardsInHand(int amount) {
	if (hand)
		delete[] hand;
	hand = new Card[amount];
	cardsInHand = amount;
}

bool Player::isInHand(Card* c, int* cardIndex) {
	for (int i = 0; i < cardsInHand; i++) {
		if (hand[i].isEqual(c)) {
			if (cardIndex)
				*cardIndex = i;
			return true;
		}
	}
	return false;
}