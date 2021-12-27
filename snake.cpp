#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int width = 20;
const int height = 20;
const int size22 = width * height;

int play_field[size22];
int head_x;
int head_y;
int direction = 1;
int lv = 0;
int snake_length = 3;
int score = 0;

bool IsGameStarted;
int diff;

void moveSnake();
void changePos();
void buildMap();
void changeDir(int x, int y);
void changePos2();
void buildEat();
void buildWall();
char changeSymb(int value, int randValue);
void startGame();


int main() {
	startGame();
}

enum ConsoleColor {
	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
	DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};

void setColor(unsigned fg, unsigned bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((bg << 4) | fg));

}

void startGame() {
	setlocale(0, "");

	cout << "Выберите уровень сложности: \n1. Лёгкий;\n2. Средний;\n3. Сложный." << endl;
	cin >> diff;

	int c = 0;

	if (diff == 1 || diff == 2 || diff == 3) {
		moveSnake();
	}
	else {

		while (true) {
			c = c + 1;

			if (c == 3) {
				diff = 1;
				moveSnake();
				break;
			}
			else {
				cout << "Выберите уровень сложности: \n1. Лёгкий;\n2. Средний;\n3. Сложный." << endl;
				cin >> diff;

				if (diff == 1 || diff == 2 || diff == 3) {
					moveSnake();
					break;
				}
			}
		}
	}

	return;
}


void moveSnake() {
	buildMap();

	IsGameStarted = true;

	while (IsGameStarted) {
		if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case 'w':
				if (direction != 3) direction = 1;
				break;
			case 'd':
				if (direction != 4) direction = 2;
				break;
			case 's':
				if (direction != 1) direction = 3;
				break;
			case 'a':
				if (direction != 2) direction = 4;
				break;
			}
		}
		changePos2();
		system("cls");
		changePos();

		switch (diff)
		{
		case 1: Sleep(200);
			break;
		case 2: Sleep(100);
			break;
		case 3: Sleep(50);
			break;
		}
	}

	setColor(Red, Black);
	cout << "Вы проиграл! " << endl;

	setColor(LightGray, Black);
	cout << "Количество набранных очков: ";

	setColor(Green, Black);
	cout << "" << score << endl;

	setColor(LightGray, Black);

	lv++;
	cout << "Уровень " << lv << endl;
	cin.ignore();

	int l;
	cout << "Желаете продолжить игру (1/0)?" << endl;
	cin >> l;

	if (l == 0) {
		return;
	}
	else {
		startGame();
	}
}

void buildEat() {
	int x = 0;
	int y = 0;

	do {
		srand(time(NULL));
		x = rand() % (width - 2) + 1;
		y = rand() % (height - 2) + 1;
	} while (play_field[x + y * width] != 0);

	play_field[x + y * width] = -2;
}

void buildWall() {
	int x = 0;
	int y = 0;

	do {
		srand(time(NULL));
		x = rand() % (width - 2) + 1;
		y = rand() % (height - 2) + 1;
	} while (play_field[x + y * width] != 0);

	play_field[x + y * width] = -4;
}


void changePos2() {
	switch (direction) {
	case 1:
		changeDir(-1, 0);
		break;
	case 2:
		changeDir(0, 1);
		break;
	case 3:
		changeDir(1, 0);
		break;
	case 4:
		changeDir(0, -1);
		break;
	}

	for (int i = 0; i < size22; i++) {
		if (play_field[i] > 0) play_field[i]--;
	}
}

void changeDir(int x, int y) {
	int x1 = head_x + x;
	int y1 = head_y + y;


	if (play_field[x1 + y1 * width] == -2) {
		snake_length = snake_length + 1;
		score = score + 1;
		buildEat();
		buildWall();
	}
	else if (play_field[x1 + y1 * width] != 0) {
		IsGameStarted = false;
	}

	head_x = x1;
	head_y = y1;
	play_field[head_x + head_y * width] = snake_length + 1;
}

void buildMap() {

	head_x = width / 5;
	head_y = height / 5;
	play_field[head_x + head_y * height] = 1;


	for (int x = 0; x < width; x++) {
		play_field[x] = -1;
		play_field[x + (height - 1) * width] = -1;

		//play_field[x / 2] = -1;
	}

	for (int y = 0; y < height; y++) {
		play_field[0 + y * height] = -3;
		play_field[(width - 1) + y * width] = -3;

		play_field[((width - 1) + y * width) / 2] = -3;
	}

	buildEat();
	buildWall();
}

void changePos() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int value2 = 0 + rand() % 10;
			cout << changeSymb(play_field[x + y * width], value2);
		}
		cout << endl;
	}
}

char changeSymb(int value, int randValue) {
	if (value > 0) {
		setColor(Green, Black);
		return 'o';
	}

	switch (value) {
	case -1:
		if (randValue >= 5) {
			setColor(Cyan, Black);
			return '!';
		}
		else {
			setColor(Yellow, Black);
			return '!';
		}
	case -2:
		setColor(Green, Black);
		return 'F';
	case -3:
		if (randValue >= 5) {
			setColor(Brown, Black);
			return '!';
		}
		else {
			setColor(Magenta, Black);
			return '!';
		}
	case -4:
		if (randValue >= 5) {
			setColor(Brown, Black);
			return '!';
		}
		else {
			setColor(Magenta, Black);
			return '!';
		}
	}
}