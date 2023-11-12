#pragma once
#include "Board.h"
#include "Player.h"
#include <map>
#include <vector>
class Game {
	int amountTeams;
	int amountPlayers;
	Board b;
	Player* players;
	bool* aiPlayers;
	int currentPlayerTurn;
public:
	Game(int players = 4, int teams = 2);
	~Game();
	void initPlayer(int player, int team, Card* hand, int amountInHand);
	void initGame(int players, int teams);
	void setPlayerAI(int player);
	bool tick();//Returns true if game still good to go
	void getHumanInput(int* x, int* y);
	//Must delete[] return pointer;
	Card* getRealCards(int amount);
	//Must delete[] return pointer
	Card* getSetCards();
	bool getAiBestLocation(int player, int* x, int* y, int* cardIndex);
	bool checkWin(int* winningTeam);
};