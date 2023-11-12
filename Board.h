#pragma once
#include "Card.h"

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
	int lenOfLineDir(int x, int y, int team, int boardDirection);
	int getAmountLines(int* team);//Returns the team with the most amount of lines
	int weighPoint(int team, int x, int y);
};