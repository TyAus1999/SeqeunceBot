#include <iostream>
#include "Game.h"

int main() {
	srand(time(NULL));
	Game g(2, 2);
	bool isGood;
	do {
		isGood = g.tick();
	} while (isGood);
	return 0;
}