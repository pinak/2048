#ifndef GAME_H
#define GAME_H
#include <vector>

class game
{
    int board[4][4], currentSlot[2], score; 
    std::vector<int> emptySlots;
    enum gameState {running, over};
    gameState state;
public:
    game();
    int twoFour(); //return 2 or 4 randomly
    void populateRandomSlot(); //populates a random empty slot on board
    void printBoard(bool update); //prints board and checks which slots are empty if update == 1
    void checkState(); //checks if game is over or not
    bool mergeUpDown(bool dryrun, bool up); //merges up if up == 1 else down 
    bool mergeLeftRight(bool dryrun, bool left); //merges left if left == 1 else right 
    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();
    void play();
};

#endif