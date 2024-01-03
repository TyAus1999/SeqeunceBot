#pragma once
#include "Card.h"
#include <unordered_map>
#include <vector>

typedef unsigned long long u64;

enum BoardDirection {
	Up,
	UpRight,
	Right,
	DownRight,
	Down,
	DownLeft,
	Left,
	UpLeft
};

struct Place {
	Card card;
	int teamOwned;//-1 when not owned
	bool isFree;
	Place() {
		teamOwned = -1;
		isFree = false;
	}
	void print() {
		card.print();
		printf("Team Owned: %i\n", teamOwned);
		printf("Is Free: %s\n", isFree ? "True" : "False");
	}
};

class Board {
	Place places[100];
public:
	Board();
	void print();
	void drawBoard();
	void initBoard();
	Place* getPlace(int x, int y);
	bool playPeice(int x, int y, int team);
	//Returns the amount of peices on the team that are in that direction
	int lenOfLineDir(int x, int y, int team, int boardDirection, int maxInDir);
	std::vector<Place*> getPlacesInDir(int x, int y, int team, int boardDirection, int maxInDir);
	//Returns list of encoded x,y where high 32bits are x, low 32bits are y
	std::vector<u64> getEncodedXYInDir(int x, int y, int team, int boardDirection, int maxInDir);
	//Decodes the xy from the u64, returns them to the pointers
	void decodeXY(u64 xy, int* x, int* y);
	//Encodes the XY and returns the encoded value
	u64 encodeXY(int x, int y);
	//Returns the team with the most amount of lines
	int getAmountLines(int* team);
	//For use with AI
	int weighPoint(int team, int x, int y);
	int amountPlayed(Card* card);
	bool checkWin(int* winningTeam, int maxLines, int maxTeams);
};