#include "Board.h"

Board::Board() {
	initBoard();
}

void Board::print() {
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			printf("X: %i, Y: %i\n", x, y);
			int offset = y * 10;
			offset += x;
			Place* p = &places[offset];
			p->print();
		}
		printf("\n");
	}
}

void Board::drawBoard() {
	std::string toDraw = "";
	for (int y = 0; y < 10; y++) {
		std::string line = "";
		for (int x = 0; x < 10; x++) {
			line += "|";
			Place* p = getPlace(x, y);
			if (p->isFree) {
				line += "  F  ";
				continue;
			}
			Card* c = &p->card;

			if (c->face > 10) {
				std::string faceName = getFaceName(c->face);
				line += " " + faceName.substr(0, 1);
			}
			else if (c->face == 10) {
				line += "10";
			}
			else if (c->face == 1) {
				line += " A";
			}
			else {
				line += " " + std::to_string(c->face);
			}
			std::string suit = getSuitName(c->suit);
			line += suit.substr(0, 1);
			if (p->teamOwned > -1) {
				line += " " + std::to_string(p->teamOwned);
			}
			else {
				line += "  ";
			}
		}
		line += "|\n";
		toDraw += line;
	}
	printf("%s", toDraw.c_str());
}

void Board::initBoard() {
	for (int i = 0; i < 100; i++) {
		Place* p = &places[i];
		switch (i) {
		case 0:
		case 9:
		case 90:
		case 99:
			p->isFree = true;
			break;
		case 1:
			p->card = Card(Spades, 10);
			break;
		case 2:
			p->card = Card(Spades, Queen);
			break;
		case 3:
			p->card = Card(Spades, King);
			break;
		case 4:
			p->card = Card(Diamonds, Ace);
			break;
		case 5:
			p->card = Card(Diamonds, 2);
			break;
		case 6:
			p->card = Card(Diamonds, 3);
			break;
		case 7:
			p->card = Card(Diamonds, 4);
			break;
		case 8:
			p->card = Card(Diamonds, 5);
			break;
		case 10:
			p->card = Card(Spades, 9);
			break;
		case 11:
			p->card = Card(Hearts, 10);
			break;
		case 12:
			p->card = Card(Hearts, 9);
			break;
		case 13:
			p->card = Card(Hearts, 8);
			break;
		case 14:
			p->card = Card(Hearts, 7);
			break;
		case 15:
			p->card = Card(Hearts, 6);
			break;
		case 16:
			p->card = Card(Hearts, 5);
			break;
		case 17:
			p->card = Card(Hearts, 4);
			break;
		case 18:
			p->card = Card(Hearts, 3);
			break;
		case 19:
			p->card = Card(Diamonds, 6);
			break;
		case 20:
			p->card = Card(Spades, 8);
			break;
		case 21:
			p->card = Card(Hearts, Queen);
			break;
		case 22:
			p->card = Card(Diamonds, 7);
			break;
		case 23:
			p->card = Card(Diamonds, 8);
			break;
		case 24:
			p->card = Card(Diamonds, 9);
			break;
		case 25:
			p->card = Card(Diamonds, 10);
			break;
		case 26:
			p->card = Card(Diamonds, Queen);
			break;
		case 27:
			p->card = Card(Diamonds, King);
			break;
		case 28:
			p->card = Card(Hearts, 2);
			break;
		case 29:
			p->card = Card(Diamonds, 7);
			break;
		case 30:
			p->card = Card(Spades, 7);
			break;
		case 31:
			p->card = Card(Hearts, King);
			break;
		case 32:
			p->card = Card(Diamonds, 6);
			break;
		case 33:
			p->card = Card(Clubs, 2);
			break;
		case 34:
			p->card = Card(Hearts, Ace);
			break;
		case 35:
			p->card = Card(Hearts, King);
			break;
		case 36:
			p->card = Card(Hearts, Queen);
			break;
		case 37:
			p->card = Card(Diamonds, Ace);
			break;
		case 38:
			p->card = Card(Spades, 2);
			break;
		case 39:
			p->card = Card(Diamonds, 8);
			break;
		case 40:
			p->card = Card(Spades, 6);
			break;
		case 41:
			p->card = Card(Hearts, Ace);
			break;
		case 42:
			p->card = Card(Diamonds, 5);
			break;
		case 43:
			p->card = Card(Clubs, 3);
			break;
		case 44:
			p->card = Card(Hearts, 4);
			break;
		case 45:
			p->card = Card(Hearts, 3);
			break;
		case 46:
			p->card = Card(Hearts, 10);
			break;
		case 47:
			p->card = Card(Clubs, Ace);
			break;
		case 48:
			p->card = Card(Spades, 3);
			break;
		case 49:
			p->card = Card(Diamonds, 9);
			break;
		case 50:
			p->card = Card(Spades, 5);
			break;
		case 51:
			p->card = Card(Clubs, 2);
			break;
		case 52:
			p->card = Card(Diamonds, 4);
			break;
		case 53:
			p->card = Card(Clubs, 4);
			break;
		case 54:
			p->card = Card(Hearts, 5);
			break;
		case 55:
			p->card = Card(Hearts, 2);
			break;
		case 56:
			p->card = Card(Hearts, 9);
			break;
		case 57:
			p->card = Card(Clubs, King);
			break;
		case 58:
			p->card = Card(Spades, 4);
			break;
		case 59:
			p->card = Card(Diamonds, 10);
			break;
		case 60:
			p->card = Card(Spades, 4);
			break;
		case 61:
			p->card = Card(Clubs, 3);
			break;
		case 62:
			p->card = Card(Diamonds, 3);
			break;
		case 63:
			p->card = Card(Clubs, 5);
			break;
		case 64:
			p->card = Card(Hearts, 6);
			break;
		case 65:
			p->card = Card(Hearts, 7);
			break;
		case 66:
			p->card = Card(Hearts, 8);
			break;
		case 67:
			p->card = Card(Clubs, Queen);
			break;
		case 68:
			p->card = Card(Spades, 5);
			break;
		case 69:
			p->card = Card(Diamonds, Queen);
			break;
		case 70:
			p->card = Card(Spades, 3);
			break;
		case 71:
			p->card = Card(Clubs, 4);
			break;
		case 72:
			p->card = Card(Diamonds, 2);
			break;
		case 73:
			p->card = Card(Clubs, 6);
			break;
		case 74:
			p->card = Card(Clubs, 7);
			break;
		case 75:
			p->card = Card(Clubs, 8);
			break;
		case 76:
			p->card = Card(Clubs, 9);
			break;
		case 77:
			p->card = Card(Clubs, 10);
			break;
		case 78:
			p->card = Card(Spades, 6);
			break;
		case 79:
			p->card = Card(Diamonds, King);
			break;
		case 80:
			p->card = Card(Spades, 2);
			break;
		case 81:
			p->card = Card(Clubs, 5);
			break;
		case 82:
			p->card = Card(Spades, Ace);
			break;
		case 83:
			p->card = Card(Spades, King);
			break;
		case 84:
			p->card = Card(Spades, Queen);
			break;
		case 85:
			p->card = Card(Spades, 10);
			break;
		case 86:
			p->card = Card(Spades, 9);
			break;
		case 87:
			p->card = Card(Spades, 8);
			break;
		case 88:
			p->card = Card(Spades, 7);
			break;
		case 89:
			p->card = Card(Diamonds, Ace);
			break;
		case 91:
			p->card = Card(Clubs, 6);
			break;
		case 92:
			p->card = Card(Clubs, 7);
			break;
		case 93:
			p->card = Card(Clubs, 8);
			break;
		case 94:
			p->card = Card(Clubs, 9);
			break;
		case 95:
			p->card = Card(Clubs, 10);
			break;
		case 96:
			p->card = Card(Clubs, Queen);
			break;
		case 97:
			p->card = Card(Clubs, King);
			break;
		case 98:
			p->card = Card(Clubs, Ace);
			break;
		}
	}
}

Place* Board::getPlace(int x, int y) {
	int offset = (y * 10) + x;
	if (offset > 99 || offset < 0)
		return 0;
	return &places[offset];
}

bool Board::playPeice(int x, int y, int team) {
	int offset = (y * 10) + x;
	if (offset >= 100)
		return false;
	Place* p = &places[offset];
	if (p->teamOwned != -1)
		return false;
	p->teamOwned = team;
	return true;
}

int Board::lenOfLineDir(int x, int y, int team, int boardDirection, int maxInDir) {
	int xDir = 0;
	int yDir = 0;
	switch (boardDirection) {
	case Up:
		xDir = 0;
		yDir = 1;
		break;
	case UpRight:
		xDir = 1;
		yDir = 1;
		break;
	case Right:
		xDir = 1;
		yDir = 0;
		break;
	case DownRight:
		xDir = 1;
		yDir = -1;
		break;
	case Down:
		xDir = 0;
		yDir = -1;
		break;
	case DownLeft:
		xDir = -1;
		yDir = -1;
		break;
	case Left:
		xDir = -1;
		yDir = 0;
		break;
	case UpLeft:
		xDir = -1;
		yDir = 1;
		break;
	}
	//Cycle through everything
	int testX = x;
	int testY = y;
	int inLine = 0;
	for (int i = 0; i < maxInDir; i++) {
		Place* testPlace = getPlace(testX, testY);
		if (!testPlace)
			return inLine;
		if (testPlace->teamOwned == team || testPlace->isFree)
			inLine++;
		else
			return inLine;
		testX += xDir;
		testY += yDir;
	}
	return inLine;
}

std::vector<Place*> Board::getPlacesInDir(int x, int y, int team, int boardDirection, int maxInDir) {
	int xDir = 0;
	int yDir = 0;
	switch (boardDirection) {
	case Up:
		xDir = 0;
		yDir = 1;
		break;
	case UpRight:
		xDir = 1;
		yDir = 1;
		break;
	case Right:
		xDir = 1;
		yDir = 0;
		break;
	case DownRight:
		xDir = 1;
		yDir = -1;
		break;
	case Down:
		xDir = 0;
		yDir = -1;
		break;
	case DownLeft:
		xDir = -1;
		yDir = -1;
		break;
	case Left:
		xDir = -1;
		yDir = 0;
		break;
	case UpLeft:
		xDir = -1;
		yDir = 1;
		break;
	}
	int testX = x;
	int testY = y;
	std::vector<Place*> toRet;
	for (int i = 0; i < maxInDir; i++) {
		Place* p = getPlace(testX, testY);
		if (!p)
			break;
		if (p->isFree || p->teamOwned == team)
			toRet.push_back(p);
		testX += xDir;
		testY += yDir;
	}
	return toRet;
}

std::vector<u64> Board::getEncodedXYInDir(int x, int y, int team, int boardDirection, int maxInDir) {
	int xDir = 0;
	int yDir = 0;
	switch (boardDirection) {
	case Up:
		xDir = 0;
		yDir = 1;
		break;
	case UpRight:
		xDir = 1;
		yDir = 1;
		break;
	case Right:
		xDir = 1;
		yDir = 0;
		break;
	case DownRight:
		xDir = 1;
		yDir = -1;
		break;
	case Down:
		xDir = 0;
		yDir = -1;
		break;
	case DownLeft:
		xDir = -1;
		yDir = -1;
		break;
	case Left:
		xDir = -1;
		yDir = 0;
		break;
	case UpLeft:
		xDir = -1;
		yDir = 1;
		break;
	}
	int testX = x;
	int testY = y;
	std::vector<u64> toRet;
	for (int i = 0; i < maxInDir; i++) {
		Place* p = getPlace(testX, testY);
		if (!p)
			break;
		else if (!p->isFree && p->teamOwned != team)
			break;
		u64 encoded = encodeXY(testX, testY);
		toRet.push_back(encoded);
		testX += xDir;
		testY += yDir;
	}
	return toRet;
}

void Board::decodeXY(u64 xy, int* x, int* y) {
	u64 temp = xy >> 32;
	*x = (int)temp;
	temp = xy<<32;
	temp = temp >> 32;
	*y = (int)temp;
}

u64 Board::encodeXY(int x, int y) {
	u64 out = x;
	out = out << 32;
	out += y;
	return out;
}

int Board::getAmountLines(int* team) {
	int teamWithHighest = -1;
	int highest = 0;
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			Place* p = getPlace(x, y);
			if (p->teamOwned < 0)
				continue;
			int total = 0;
			for (int dir = 0; dir < 8; dir++)
				total += lenOfLineDir(x, y, p->teamOwned, dir, 5);
			if (total > highest) {
				highest = total;
				teamWithHighest = p->teamOwned;
			}
		}
	}
	*team = teamWithHighest;
	return highest;
}

int Board::weighPoint(int team, int x, int y) {
	Place* test = getPlace(x, y);
	if (!test || test->teamOwned >= 0)
		return -1;
	int weight = 0;
	for (int dir = 0; dir < 8; dir++) {
		weight += lenOfLineDir(x, y, team, dir, 5);
	}
	return weight;
}

int Board::amountPlayed(Card* card) {
	if (card->face == 0 || card->suit == 0)
		return 0;
	int amountRet = 0;
	for (int i = 0; i < 100; i++) {
		Place* testPlace = &places[i];
		if (testPlace->isFree || testPlace->teamOwned == -1)
			continue;
		Card* testCard = &testPlace->card;
		if (!testCard->isEqual(card))
			continue;
		amountRet++;
	}
	return amountRet;
}

bool Board::checkWin(int* winningTeam, int maxLines, int maxTeams) {
	for (int team = 0; team < maxTeams; team++) {
		//u64 for coord, bool just because I need a pair value thing
		std::unordered_map<u64, bool> usedCoords;
		int lines = 0;
		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				for (int dir = 0; dir < 8; dir++) {
					std::vector<u64> inDir = getEncodedXYInDir(x, y, team, dir, 10);
					int size = inDir.size();
					if (size < 5)
						continue;
					else if (size > 5)
						continue;
					lines++;
					//for (int i = 0; i < size; i++) {
					//	auto didFind = usedCoords.find(inDir[i]);
					//	if (didFind != usedCoords.end())
					//		continue;
					//	usedCoords.insert(std::pair<u64, bool>(inDir[i], true));
					//}
				}
			}
		}
		if (lines/2 >= maxLines) {
			*winningTeam = team;
			return true;
		}
		//for (auto coord : usedCoords) {
		//	int x, y;
		//	decodeXY(coord.first, &x, &y);
		//	printf("X: %i, Y: %i\n", x, y);
		//}
	}
	return false;
	//for (int team = 0; team < maxTeams; team++) {
	//	//u64 is coord, int is amount of times
	//	std::unordered_map<u64, int> coordsOfWins;
	//	int lines = 0;
	//	for (int x = 0; x < 10; x++) {
	//		for (int y = 0; y < 10; y++) {
	//			for (int dir = 0; dir < 8; dir++) {
	//				std::vector<u64> inDir = getEncodedXYInDir(x, y, team, dir, 10);
	//				if (inDir.size() < 5)
	//					continue;
	//				for (int i = 0; i < inDir.size(); i++) {
	//					auto didFind = coordsOfWins.find(inDir[i]);
	//					if (didFind == coordsOfWins.end())
	//						coordsOfWins.insert(std::pair<u64, int>(inDir[i], 1));
	//					else
	//						didFind->second = didFind->second + 1;
	//				}
	//			}
	//		}
	//	}
	//	printf("Team: %i\n", team);
	//	for (auto cw : coordsOfWins) {
	//		int x, y;
	//		decodeXY(cw.first, &x, &y);
	//		printf("\tX: %i, Y: %i, Amount: %i\n", x, y, cw.second/2);
	//	}
	//}
	//return false;
}