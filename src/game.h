#ifndef GAME_H
#define GAME_H
#include <vector>
#include <QObject>

#define boardSize 4

class Game : public QObject
{
    Q_OBJECT
public:
    Game(QObject* parent = 0);
    void play(int direction);
    int get(int i, int j) const;
    int currentScore() const { return m_score; }

    enum direction {up = 0, down, left, right};
signals:
    void boardChanged();
    void gameIsOver();
private:
    int twoFour(); //return 2 or 4 randomly
    void populateRandomSlot(); //populates a random empty slot on board
    void printBoard(bool update); //prints board and checks which slots are empty if update == 1
    bool gameOver(); //checks if game is over or not
    bool mergeUpDown(bool dryrun, bool up); //merges up if up == 1 else down
    bool mergeLeftRight(bool dryrun, bool left); //merges left if left == 1 else right
    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();

    int m_board[boardSize][boardSize];
    int m_currentSlot[2];
    int m_score;
    std::vector<int> m_emptySlots;
};

#endif