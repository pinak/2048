#include "game.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
using namespace std;

game::game()
{
	state = running;
	srand(time(NULL)); // seed the random function
	for(int i = 0; i < 4; i++) 
	{
		for(int j = 0; j < 4; j++)
		{
			board[i][j] = 0; //set board to empty
			emptySlots.push_back(10*i + j); //adds all slot to list of empty slots
		}
	}
	score = 0;
	populateRandomSlot();
	populateRandomSlot();
}

int game::twoFour()
{
	int a = rand() % 2;
	if(a == 0)
		return 2;
	return 4;
}

void game::populateRandomSlot()
{
	int size = emptySlots.size();
	if(size == 0)
		cout << "error: no empty slots available";
	else
	{
		random_shuffle(emptySlots.begin(), emptySlots.end());
		currentSlot[0] = emptySlots.at(size - 1) / 10;
		currentSlot[1] = emptySlots.at(size - 1) % 10;
		emptySlots.pop_back();
		board[currentSlot[0]][currentSlot[1]] = twoFour();
	}
}

void game::printBoard(bool update)
{
	if(update)
		emptySlots.clear();
	cout << "score: " << score << endl;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(!board[i][j])
			{
				cout << setw(4) << " ";
				if(update)
					emptySlots.push_back((10*i) + j);
			}

			else
				cout << setw(4) << board[i][j];
			cout <<"  ";
		}
		cout << "\n";
	}
}

void game::checkState()
{
	if(emptySlots.size() > 0)
		return;
	else
	{
		if(mergeUpDown(1, 1) == 0 && mergeLeftRight(1, 1) == 0)
		{
			state = over;
			return;
		}
	}
	return;
}



void game::play()
{	
	printBoard(0);
	char direction;
	bool move, merge;
	while(state == running)
	{
		cin >> direction;
		switch(direction)
		{
			case 'w':
			move = moveUp();
			merge = mergeUpDown(0, 1);
			moveUp();
			break;

			case 's':
			move = moveDown();
			merge = mergeUpDown(0, 0);
			moveDown();
			break;

			case 'a':
			move = moveLeft();
			merge = mergeLeftRight(0, 1);
			moveLeft();
			break;

			case 'd':
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
			checkState();
			system("clear");
			cout << endl;
			printBoard(0);
			move = 0;
			merge = 0;

		}
		else
			cout << "invalid move\n";
	}
}


bool game::mergeUpDown(bool dryrun, bool up)
{
	bool possible = 0;
	int i;
	for(i = 0; i < 3; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(board[i][j] == 0)
				continue;
			if(board[i][j] == board[i + 1][j])
			{
				possible = 1;
				if(dryrun)
					return possible;
				else
				{	if(up)
					{
						board[i][j] *= 2;
						board[i + 1][j] = 0;
						score += board[i][j];
					}
					else //for down
					{
						board[i][j] = 0;
						board[i + 1][j] *= 2;
						score += board[i + 1][j];
					}
				}
			}
		}	
	}
	return possible;
}

bool game::moveUp()
{
	bool possible = 0;
	int curRow;
	for(int i = 1; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			curRow = i;
			while(board[curRow - 1][j] == 0)
			{
				if(curRow == 0 || board[curRow][j] == 0)
					break;
				board[curRow - 1][j] = board[curRow][j];
				board[curRow][j] = 0;
				possible = 1;
				curRow--;
			}	
			
		}
	}
	return possible;
}


bool game::moveDown()
{
	bool possible = 0;
	int curRow;
	for(int i = 2; i >= 0; i--)
	{
		for(int j = 0; j < 4; j++)
		{
			curRow = i;
			while(board[curRow + 1][j] == 0)
			{
				if(curRow == 3 || board[curRow][j] == 0)
					break;
				board[curRow + 1][j] = board[curRow][j];
				board[curRow][j] = 0;
				possible = 1;
				curRow++;
			}	
			
		}
	}
	return possible;
}

bool game::mergeLeftRight(bool dryrun, bool left)
{
	bool possible = 0;
	int j;
	for(j = 0; j < 3; j++)
	{
		for(int i = 0; i < 4; i++)
		{
			if(board[i][j] == 0)
				continue;
			if(board[i][j] == board[i][j + 1])
			{
				possible = 1;
				if(dryrun)
					break;
				else
				{
					if(left)
					{
						board[i][j] *= 2;
						board[i][j + 1] = 0;
						score += board[i][j];
					}
					else //for right
					{
						board[i][j] = 0;
						board[i][j + 1] *= 2;
						score += board[i][j + 1];
					}
				}
			}
		}	
	}
	return possible;
}

bool game::moveLeft()
{
	bool possible = 0;
	int curCol;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 1; j < 4; j++)
		{
			curCol = j;
			while(board[i][curCol - 1] == 0)
			{
				if(curCol == 0 || board[i][curCol] == 0)
					break;
				board[i][curCol- 1] = board[i][curCol];
				board[i][curCol] = 0;
				curCol--;
				possible = 1;
			}	
				
		}
	}
	return possible;
}


bool game::moveRight()
{
	bool possible = 0;
	int curCol;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 2; j >=0; j--)
		{
			curCol = j;
			while(board[i][curCol + 1] == 0)
			{
				if(curCol == 3 || board[i][curCol] == 0)
					break;
				board[i][curCol + 1] = board[i][curCol];
				board[i][curCol] = 0;
				curCol++;
				possible = 1;
			}	
				
		}
	}
	return possible;
}