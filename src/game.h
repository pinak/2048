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
	int twoFour(); // return 2 or 4 randomly
	void populateRandomSlot(); // populates a random empty slot on board
	void printBoard(bool); // prints board and checks which slots are empty of argument is 1
	void checkState(); //checks if game is over or not
	bool mergeUpDown(bool dryrun, bool up); //merges up if up == 1 else down 
	bool mergeLeftRight(bool dryrun, bool left);//merges left if left else right 
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	void play();
};

#endif