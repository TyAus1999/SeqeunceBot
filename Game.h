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
	Game(int players = 2, int teams = 2);
	~Game();
	void reset();
	void initPlayer(int player, int team, Card* hand, int amountInHand);
	void initGame(int players, int teams);
	Board* getBoardRender();
	void setPlayerAI(int player);
	bool tick();//Returns true if game still good to go
	void getHumanInput(int* x, int* y);
	//Must delete[] return pointer;
	Card* getRealCards(int amount);
	//Must delete[] return pointer
	Card* getSetCards();
	//Must delete[] return pointer, returns set that is valid and not in the other players hands
	Card* getValidRandomCards(int amount);
	//Used for getting a random valid card that has not been played yet
	Card getValidRandomPickup();
	

	bool getAiBestLocation(int player, int* x, int* y, int* cardIndex);
	bool getAIBestLocation2(int player, int* x, int* y, int* cardIndex);
	int aiWeighPoint(int x, int y, int team);
};