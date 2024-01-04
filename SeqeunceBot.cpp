#include <iostream>
#include "Game.h"

void boardCheckWinTest() {
	Board b;
	for (int i = 0; i < 7; i++)
		b.playPeice(2 + i, 2, 0);
	for (int i = 0; i < 5; i++)
		b.playPeice(4, 2 + i, 0);
	b.drawBoard();
	int winningTeam;
	if (b.checkWin(&winningTeam, 2, 2)) {
		printf("Team %i, won\n", winningTeam);
	}
}

int main() {
	srand(time(NULL));
	boardCheckWinTest();
	return 0;
	Game g(2, 2);
	bool isGood;
	do {
		isGood = g.tick();
		system("pause");
	} while (isGood);
	return 0;
}