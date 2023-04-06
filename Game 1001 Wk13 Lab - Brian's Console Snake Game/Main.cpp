#include <iostream>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include <string>
#include "Food.h"
#include "Snake.h"

HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
const COORD HOME_COORD({ 0,0 });

float difficulty = 1;
int score = 0;

Snake snake({ WIDTH / 2, HEIGHT / 2 }, 1);
Food food;

void init();
void handleInput();
void update();
void gameOver();

int main()
{
	init();

	do {
		handleInput();
		snake.move();

		if (snake.hasFood(food.getPos()))
		{
			snake.addLength();
			food.placeFood(snake);
			score++;
			difficulty *= HARD_FACTOR;
		}

		update();

		double wait = (snake.getDirection() == n || snake.getDirection() == s) ? 300 : 200;
		Sleep(wait * difficulty);
	} while (!snake.hasCollided());

	gameOver();
}

void init()
{
	srand(time(NULL));
	food.placeFood(snake);
}

void drawChar(COORD p, char c)
{
	SetConsoleCursorPosition(screen, p);
	std::cout << c;
	SetConsoleCursorPosition(screen, HOME_COORD);
}

void drawBackground()
{
	std::string wall, sides;

	wall.assign(WIDTH, '#');
	sides = '#' + sides.assign(WIDTH - 2, ' ') + '#';

	std::cout << "SCORE : " << score << "\n\n";
	std::cout << wall << std::endl;
	for (int i = 0; i < HEIGHT - 2; i++)
		std::cout << sides << std::endl;
	std::cout << wall << std::endl;
}

void drawSnake()
{
	COORD coord = { 0, 0 };
	Pos snakePos = snake.getPos();
	std::vector<Pos> snakeBody = snake.getBody();

	for (int i = 0; i < snakeBody.size(); i++)
	{
		coord.X = snakeBody[i].x;
		coord.Y = snakeBody[i].y;
		if (i < snakeBody.size() - 1)
			drawChar(coord, 'o');
		else
			drawChar(coord, 'O');
	}
}

void drawFood()
{
	Pos foodPos = food.getPos();

	COORD coord = { 0, 0 };
	coord.X = foodPos.x;
	coord.Y = foodPos.y;
	drawChar(coord, 'F');
}

void clearScreen()
{
	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	DWORD count, cellCount;

	if (!GetConsoleScreenBufferInfo(screen, &csbInfo))
		return;
	cellCount = csbInfo.dwSize.X * csbInfo.dwSize.Y;

	if (!FillConsoleOutputCharacter(screen, (TCHAR)' ', cellCount, HOME_COORD, &count))
		return;
}

void update()
{
	//system("cls"); 
	clearScreen();
	drawBackground();
	drawSnake();
	drawFood();
}


void handleInput()
{
	if (_kbhit())
	{
		int ch = _getch();
		if (ch == 224 || ch == 0) // 224 indicates arrow keys
		{
			switch (_getch()) // second input is arrow
			{
			case 72: ch = 'w'; break;
			case 75: ch = 'a'; break;
			case 80: ch = 's'; break;
			case 77: ch = 'd'; break;
			}
		}
		switch (ch)
		{
		case 'w': if (snake.getDirection() != s) snake.setDirection(n); break;
		case 'a': if (snake.getDirection() != e) snake.setDirection(w); break;
		case 's': if (snake.getDirection() != n) snake.setDirection(s); break;
		case 'd': if (snake.getDirection() != w) snake.setDirection(e); break;
		}
	}
}

void gameOver()
{
	COORD coord;
	coord.X = (WIDTH / 2) - 5;
	coord.Y = (HEIGHT / 2) + 1;
	SetConsoleCursorPosition(screen, coord);
	std::cout << "Game over!";

	Sleep(5000);
	coord.X = 0;
	coord.Y = HEIGHT + 2;
	SetConsoleCursorPosition(screen, coord);
}