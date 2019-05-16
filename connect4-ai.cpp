#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>

using namespace std;

// -- Declarations

// -- Global variables -- //
char table[7][7];
char HI = 'O', AI = 'X', choice = '0';

int last_play;
int full = 0;

bool AImove = false;

// -- Function declarations -- //

void setTable();
void show();
void enter();

void gamemode();
void changePlayer();
void resetPlayer();
void restart();

bool check_num(char digitx);
bool check_full(int column);

bool check(char player, char arr[][7], int rowsize);
bool checkrow(char player, char arr[][7], int rowsize);
bool checkcol(char player, char arr[][7], int rowsize);
bool checkdia(char player, char arr[][7], int rowsize);
bool checkinvdia(char player, char arr[][7], int rowsize);


// -- AI Functions -- //

void AI_TURN();
void AI_ATT();
void AI_DEF();
void AI_NRML();

// ------------------------------------------------------

//-- Main

int main() {
	char currentP;
	gamemode();
	setTable();
	resetPlayer();
	if (choice == '1') {
		while (1) {
			show();
			enter();

			if (check(HI, table, 7)) {
				show();
				cout << "HI won\n";
				break;
			}

			AI_TURN();

			if (check(AI, table, 7)) {
				show();
				cout << "AI won\n";
				break;
			}
		}
	}
	else {
		while (1) {
			currentP = HI;
			show();
			enter();
			if (check(currentP, table, 7)) {
				show();
				if (currentP == 'O')
					cout << "Player O won\n";
				else
					cout << "Player X won\n";
				break;
			}
			changePlayer();
		}
	}
	restart();
}

// -- Actual typing
void setTable() {

	for (int i = 0; i < 7; i++)
	{
		for (int z = 0; z < 7; z++)
		{
			table[i][z] = ' '; // setting all the table to the same ' ' value
		}
	}
}

void show() {
	system("cls");
	system("color b");

	cout << "Endless Possibilities Team | O6U\n_________________________________\n\n\a";
	if (choice == '1')
		cout << "Player 1 = O\nAI = X\n";
	else
		cout << "Player 1 = O\nPlayer 2 = X\n";

	cout << "\t\t\t      1           2           3           4           5           6           7" << endl;
	cout << "\t\t\t+-----------+-----------+-----------+-----------+-----------+-----------+-----------+" << endl;

	for (int row = 0; row < 7; row++) {
		cout << "\t\t\t";
		for (int col = 0; col < 7; col++) {
			cout << "|     " << table[row][col] << "     ";
		}
		cout << "|";
		cout << "\n\t\t\t+-----------+-----------+-----------+-----------+-----------+-----------+-----------+" << endl;
	}

	cout << "Last play: " << last_play << endl;
	if (choice == '2') {
		if (HI == 'O')
			cout << "Player O turn\n";
		else
			cout << "Player X turn\n";
	}
}

void enter() {

	char digit;

	int digit_again;

	cout << "Enter a place to play: ";
	cin >> digit;

	digit_again = digit - 48;

	if (!check_num(digit) || check_full(digit_again)) {
		cout << "Enter a valid place\n\n";
		enter();
	}

	for (int i = 0; i < 8; i++) {
		if (table[i][digit_again - 1] != ' ') {
			table[i - 1][digit_again - 1] = HI;
			break;
		}
	}

}

void gamemode() {
	system("color a");
	cout << "Endless Possibilities Team | O6U\n_________________________________\n\n\a";
	cout << "Your prefered gamemode is:\n";
	cout << "1. Player vs AI\n";
	cout << "2. Player 1 vs Player 2\n";
	cin >> choice;

	if (choice != '1' && choice != '2')
		gamemode();
}

void changePlayer() {
	if (HI == 'O')
		HI = 'X'; // P2
	else
		HI = 'O'; // P1
}

void resetPlayer() {
	HI = 'O';
}

void restart() {
	int x ;
	string text = "Restarting in 3";
	cout << text;
	Sleep(1000);
	text.replace(14, 1, "2");
	cout << "\r" << text;
	Sleep(1000);
	text.replace(14, 1, "1");
	cout << "\r" << text << endl;
	Sleep(1000);
	system("cls");
	main();
}

//-- Checkers
bool check_num(char digitx) {
	int ascii = digitx;

	if (ascii > 47 && ascii < 56)
		return true;
	else
		return false;
}

bool check_full(int column) {
	int counter = 0;
	for (int i = 0; i < 7; i++)
	{
		if (table[i][column - 1] != ' ')
			counter++;
	}
	if (counter == 7)
		return true;
	else
		return false;
}

bool check(char player, char arr[][7], int rowsize) {
	if (checkrow(player, arr, rowsize) == true)
		return true;
	else if (checkcol(player, arr, rowsize) == true)
		return true;
	else if (checkdia(player, arr, rowsize) == true)
		return true;
	else if (checkinvdia(player, arr, rowsize) == true)
		return true;
	else
		return false;
}

bool checkrow(char player, char arr[][7], int rowsize) {

	for (int i = 0; i < 7; i++) {
		for (int z = 0; z < 7; z++) {
			if (z < 4) {
				if (table[i][z] == player) {
					if (table[i][z] == table[i][z + 1] && table[i][z] == table[i][z + 2] && table[i][z] == table[i][z + 3]) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool checkcol(char player, char arr[][7], int rowsize) {

	for (int i = 0; i < 7; i++) {
		for (int z = 0; z < 7; z++) {
			if (i < 4) {
				if (table[i][z] == player) {
					if (table[i][z] == table[i + 1][z] && table[i][z] == table[i + 2][z] && table[i][z] == table[i + 3][z]) {
						return true;
					}

				}
			}
		}
	}
	return false;
}

bool checkdia(char player, char arr[][7], int rowsize) {

	for (int row = 0; row < 6; row++) // Check {\}
	{
		for (int col = 0; col < 7; col++)
		{
			if (table[row][col] == player)
			{
				if ((table[row][col] == table[row + 1][col + 1]) && (table[row + 1][col + 1] == table[row + 2][col + 2]) && (table[row + 2][col + 2] == table[row + 3][col + 3]))
				{
					return true;
				}

			}
		}
	}

	return false;

}

bool checkinvdia(char player, char arr[][7], int rowsize) {
	for (int row = 0; row < 6; row++) // Check { / }
	{
		for (int col = 6; col >= 0; col--)
		{
			if (table[row][col] == player)
			{
				if ((table[row][col] == table[row + 1][col - 1]) && (table[row + 1][col - 1] == table[row + 2][col - 2]) && (table[row + 2][col - 2] == table[row + 3][col - 3]))
				{
					return true;
				}
			}
		}
	}
	return false;
}

// -- AI

void AI_TURN() {
	AImove = false;

	if (!AImove)
		AI_ATT();
	if (!AImove)
		AI_DEF();
	if (!AImove)
		AI_NRML();

}

void AI_ATT() {

	char backup = ' ';

	for (int i = 0; i < 7; i++)
	{
		for (int z = 0; z < 7; z++)
		{
			if (table[i][z] != AI && table[i][z] != HI && table[i - 1][z] != backup) {
				table[i][z] = AI;
				if (check(AI, table, 7) == true) {
					last_play = i + 1;
					table[i][z] = AI;
					AImove = true;
					return;
				}
				else
					table[i][z] = backup;
			}
		}
	}

}

void AI_DEF() {
	char backup = ' ';

	for (int i = 0; i < 7; i++)
	{
		for (int z = 0; z < 7; z++)
		{
			if (table[i][z] != AI && table[i][z] != HI && table[i + 1][z] != backup) {
				table[i][z] = HI;
				if (check(HI, table, 7) == true) {
					last_play = i + 1;
					table[i][z] = AI;
					AImove = true;
					return;
				}
				else
					table[i][z] = backup;
			}

		}

	}

}

void AI_NRML() {

	int x;

	show();
	cout << "Thinking ..." << endl;
	Sleep(1000);
	system("CLS");

	srand(time(0));
	x = (1 + (rand() % (7)));

	if (check_full(x))
		AI_NRML();

	for (int i = 0; i < 8; i++) {
		if (table[i][x - 1] != ' ') {
			table[i - 1][x - 1] = AI;
			last_play = x;
			AImove = true;
			full++;
			return;
		}
	}
	AI_NRML();
}