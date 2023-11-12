#include "Card.h"

Card::Card(int suit, int face) {
	this->suit = suit;
	this->face = face;
}

void Card::print() {
	std::string sName = getSuitName(suit);
	std::string fName = getFaceName(face);
	std::cout << "Suit: " << sName << ", Face: " << fName << "\n";
}

void Card::setSuit(int suit) {
	this->suit = suit;
}

void Card::setFace(int face) {
	this->face = face;
}

bool Card::isEqual(Card* c) {
	return c->face == face && c->suit == suit;
}

bool Card::operator==(const Card& other) {
	return other.face == face && other.suit == suit;
}