#include <iostream>
#include "Game.h"

int main() {
	Game g(2, 2);
	bool isGood;
	do {
		isGood = g.tick();
	} while (isGood);
	return 0;
}