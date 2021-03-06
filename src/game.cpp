#include "game.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

using namespace std;

Game::Game(QObject* parent)
    : QObject(parent)
{
    srand(time(NULL)); // seed the random function
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            m_board[i][j] = 0; //set board to empty
            m_emptySlots.push_back(10*i + j); //adds all slot to list of empty slots
        }
    }
    m_score = 0;
    populateRandomSlot();
    populateRandomSlot();
}

int Game::twoFour()
{
    int a = rand() % 2;
    if(a == 0)
        return 2;
    return 4;
}

void Game::populateRandomSlot()
{
    int size = m_emptySlots.size();
    if(size == 0)
        cout << "error: no empty slots available";
    else
    {
        random_shuffle(m_emptySlots.begin(), m_emptySlots.end());
        m_currentSlot[0] = m_emptySlots.at(size - 1) / 10;
        m_currentSlot[1] = m_emptySlots.at(size - 1) % 10;
        m_emptySlots.pop_back();
        m_board[m_currentSlot[0]][m_currentSlot[1]] = twoFour();
    }
}

void Game::printBoard(bool update)
{
    if(update)
        m_emptySlots.clear();
    cout << "score: " << m_score << endl;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(!m_board[i][j])
            {
                cout << setw(4) << " ";
                if(update)
                    m_emptySlots.push_back((10*i) + j);
            }

            else
                cout << setw(4) << m_board[i][j];
            cout <<"  ";
        }
        cout << "\n";
    }
}

bool Game::gameOver()
{
    if(m_emptySlots.size() > 0)
        return false;
    else
    {
        if(mergeUpDown(1, 1) == 0 && mergeLeftRight(1, 1) == 0)
        {
            return true;
        }
    }
    return false;
}



void Game::play(int direction)
{
    printBoard(0);
    bool move = 0, merge = 0;
    switch(direction)
    {
        case up:
        move = moveUp();
        merge = mergeUpDown(0, 1);
        moveUp();
        break;

        case down:
        move = moveDown();
        merge = mergeUpDown(0, 0);
        moveDown();
        break;

        case left:
        move = moveLeft();
        merge = mergeLeftRight(0, 1);
        moveLeft();
        break;

        case right:
        move = moveRight();
        merge = mergeLeftRight(0, 0);
        moveRight();
        break;
    }
    //cout << "\nmove: " << move << endl << "merge: " << merge << endl;
    if(move || merge)
    {
        system("clear");
        printBoard(1);
        populateRandomSlot();
        emit boardChanged();
        if (gameOver()) {
            emit gameOver();
        }
        system("clear");
        cout << endl;
        printBoard(0);
    }
    else
        cout << "invalid move\n";
}


bool Game::mergeUpDown(bool dryrun, bool up)
{
    bool possible = 0;
    int i;
    for(i = 0; i < 3; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(m_board[i][j] == 0)
                continue;
            if(m_board[i][j] == m_board[i + 1][j])
            {
                possible = 1;
                if(dryrun)
                    return possible;
                else
                {   if(up)
                    {
                        m_board[i][j] *= 2;
                        m_board[i + 1][j] = 0;
                        m_score += m_board[i][j];
                    }
                    else //for down
                    {
                        m_board[i][j] = 0;
                        m_board[i + 1][j] *= 2;
                        m_score += m_board[i + 1][j];
                    }
                }
            }
        }
    }
    return possible;
}

bool Game::moveUp()
{
    bool possible = 0;
    int curRow;
    for(int i = 1; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            curRow = i;
            while(m_board[curRow - 1][j] == 0)
            {
                if(curRow == 0 || m_board[curRow][j] == 0)
                    break;
                m_board[curRow - 1][j] = m_board[curRow][j];
                m_board[curRow][j] = 0;
                possible = 1;
                curRow--;
            }

        }
    }
    return possible;
}


bool Game::moveDown()
{
    bool possible = 0;
    int curRow;
    for(int i = 2; i >= 0; i--)
    {
        for(int j = 0; j < 4; j++)
        {
            curRow = i;
            while(m_board[curRow + 1][j] == 0)
            {
                if(curRow == 3 || m_board[curRow][j] == 0)
                    break;
                m_board[curRow + 1][j] = m_board[curRow][j];
                m_board[curRow][j] = 0;
                possible = 1;
                curRow++;
            }

        }
    }
    return possible;
}

bool Game::mergeLeftRight(bool dryrun, bool left)
{
    bool possible = 0;
    int j;
    for(j = 0; j < 3; j++)
    {
        for(int i = 0; i < 4; i++)
        {
            if(m_board[i][j] == 0)
                continue;
            if(m_board[i][j] == m_board[i][j + 1])
            {
                possible = 1;
                if(dryrun)
                    break;
                else
                {
                    if(left)
                    {
                        m_board[i][j] *= 2;
                        m_board[i][j + 1] = 0;
                        m_score += m_board[i][j];
                    }
                    else //for right
                    {
                        m_board[i][j] = 0;
                        m_board[i][j + 1] *= 2;
                        m_score += m_board[i][j + 1];
                    }
                }
            }
        }
    }
    return possible;
}

bool Game::moveLeft()
{
    bool possible = 0;
    int curCol;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 1; j < 4; j++)
        {
            curCol = j;
            while(m_board[i][curCol - 1] == 0)
            {
                if(curCol == 0 || m_board[i][curCol] == 0)
                    break;
                m_board[i][curCol- 1] = m_board[i][curCol];
                m_board[i][curCol] = 0;
                curCol--;
                possible = 1;
            }

        }
    }
    return possible;
}


bool Game::moveRight()
{
    bool possible = 0;
    int curCol;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 2; j >=0; j--)
        {
            curCol = j;
            while(m_board[i][curCol + 1] == 0)
            {
                if(curCol == 3 || m_board[i][curCol] == 0)
                    break;
                m_board[i][curCol + 1] = m_board[i][curCol];
                m_board[i][curCol] = 0;
                curCol++;
                possible = 1;
            }

        }
    }
    return possible;
}

int Game::get(int i, int j) const
{
    return m_board[i][j];
}
