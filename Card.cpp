#include "Card.h"

Card::Card(int suit, int face) {
	this->suit = suit;
	this->face = face;
	if (face == Jack && (suit == Clubs || suit == Diamonds))
		is2Eye = true;
	else
		is2Eye = false;
}

void Card::print() {
	std::string sName = getSuitName(suit);
	std::string fName = getFaceName(face);
	std::cout << "Suit: " << sName << ", Face: " << fName << "\n";
}

bool Card::isEqual(Card* c) {
	return c->face == face && c->suit == suit;
}

void Card::setRandom() {
	suit = rand() % 4;
	suit++;
	face = rand() % 13;
	face++;
}

bool Card::isValid() {
	if (suit == NoSuit || face == NoFace)
		return false;
	return true;
}

bool Card::operator==(const Card& other) {
	return other.face == face && other.suit == suit;
}