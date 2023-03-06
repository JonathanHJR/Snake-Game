#include <iostream>
#include <conio.h> //For _kbhit() & _getch()
#include <Windows.h> //For Sleep() 
//Declare all global variables
using namespace std;
bool gameOver;
const int width = 20; //Map
const int height = 20;
int x, y, fruitX, fruitY, score; //Game elements, snake head, fruit
int tailX[100], tailY[100]; //Array for tail x, y coordinates. 100 const elements size. Determined during compile time, before program runtime.
int nTail; //Specify length of tail
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN}; //Enumerated data type is a type whose legal values consist of a fixed set of constants eg. Compass directions N, S, E, W
eDirection dir; //Direction of snake
void Setup() //Snake, fruit, score
{
	gameOver = false;
	dir = STOP; //Snake will not move at start
	x = width / 2; //Snake centered on the map
	y = height / 2;
	fruitX = rand() % width; //Position of fruit. Returns a pseudo-random integral number in the range between 0 and RAND_MAX.
	fruitY = rand() % height;
	score = 0;
}
void Draw()
{
	system("cls"); //Windows command clears console terminal
	for (int i = 0; i <= width; i++) //Print top wall
	{
		cout << "#";
	}
	cout << endl; //Move to next line. Manipulator/command, operating system will flush the output buffer and insert a new line. Flushing is also done periodically normally.

	for (int i = 0; i <= height; i++) //Print map column by column, iterate vertically
	{
		for (int j = 0; j <= width; j++) //Row by row, iterate horizontally
		{
			if ((j == 0) || (j == width))
			{
				cout << "#";
			}
			else if ((i == y) && (j == x))
			{
				cout << "O";
			}
			else if ((i == fruitY) && (j == fruitX))
			{
				cout << "F";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++) //Print tail if true
				{
					if ((tailY[k] == i) && (tailX[k] == j)) //Print tail wherever it goes in the map
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
				{
					cout << " "; 
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i <= width; i++) //Print bottom wall
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score:" << score << endl;
}
void Input()
{
	if (_kbhit()) //Will loop until a key has been pressed then returns non-zero int
	{
		switch (_getch()) 
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
		}
	}
}
void Logic()
{
	if ((x == fruitX) && (y == fruitY)) //If snake reaches fruit, increase score & shift fruit locations
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++; //Increase tail length by one
	}

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	// if ((x > width) || (x < 0) || (y > height) || (y < 0)) //Ensures game terminates once snake goes out of map
	// {
	// 	   gameOver = true;
	// }

	if (x >= width) //Makes snake go to the other end of the map
	{
		x = 0;
	}

	else if (x < 0)
	{
		x = width - 1;
	}

	if (y >= width)
	{
		y = 0;
	}

	else if (y < 0)
	{
		y = width - 1;
	}

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
}
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(100); //Slow down flickering & movement of snake
	}
}