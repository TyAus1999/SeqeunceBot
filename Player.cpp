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

void Player::printHand() {
	if (!hand) {
		printf("No cards in hand for player!\n");
		return;
	}
	std::string toDisp = "";
	for (int i = 0; i < cardsInHand; i++) {
		Card* c = &hand[i];
		std::string faceName = getFaceName(c->face);
		std::string suitName = getSuitName(c->suit);
		toDisp.append(faceName);
		toDisp.append(" of ");
		toDisp.append(suitName);
		if (i + 1 < cardsInHand)
			toDisp.append(", ");
	}
	printf("%s\n", toDisp.c_str());
}