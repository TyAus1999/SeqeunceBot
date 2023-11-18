#pragma once
#include <iostream>
#include <string>
enum CardSuit {
	NoSuit,
	Diamonds,
	Clubs,
	Hearts,
	Spades
};

static std::string getSuitName(int suit) {
	std::string out = "Invalid Suit";
	if (suit<Diamonds || suit>Spades)
		return out;
	switch (suit) {
	case Diamonds:
		out = "Diamonds";
		break;
	case Clubs:
		out = "Clubs";
		break;
	case Hearts:
		out = "Hearts";
		break;
	case Spades:
		out = "Spades";
		break;
	}
	return out;
}

enum CardFace {
	NoFace,
	Ace,
	Jack = 11,
	Queen,
	King,
};

static std::string getFaceName(int face) {
	std::string out = "Invalid Face";
	if (face > King || face < Ace)
		return out;
	switch (face) {
	case 0:
		break;
	case Ace:
		out = "Ace";
		break;
	case Jack:
		out = "Jack";
		break;
	case Queen:
		out = "Queen";
		break;
	case King:
		out = "King";
		break;
	default:
		out = std::to_string(face);
	}
	return out;
}

class Card {
public:
	int suit;
	int face;
	Card(int s = NoSuit, int f = NoFace);
	/*
	Print function,
	Prints the values of the Card
	*/
	void print();
	bool isEqual(Card* c);
	void setRandom();
	bool isValid();
	inline bool operator==(const Card& left);
};