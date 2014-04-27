#ifndef GAME_H
#define GAME_H
#include <vector>

class game
{
	int board[4][4];
	std::vector<int> emptySlots;
	int currentSlot[2];
	enum gameState {running, over};
	gameState state;
public:
	game();
	int twoFour();
	void populateRandomSlot();
	void printBoard(bool);
	void checkState();
	bool mergeUp(bool);
	bool mergeDown(bool);
	bool mergeLeft(bool);
	bool mergeRight(bool);
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	void play();
};

#endif