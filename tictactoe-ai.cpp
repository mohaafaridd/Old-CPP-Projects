#pragma comment(lib, "Winmm.lib")
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <Mmsystem.h>
using namespace std;

// Global variables
bool AImove = false;
string **table, AI = "X", HI = "O", choice = "0", currentP;
string playfirst = "blabla", last_play;
string* randarray;
int tablesize;
int full = 0;

// Prototypes
void setTable();

void show();
void enter();
void emptyPlace(string x);

void gamemode();
void changePlayer();
void resetPlayer();
void restart();

void chooseSize();
void decidePlayer();
void isRepeat();

bool check(string player, string **arr, int rowsize);
bool checkrow(string player, string **arr, int rowsize);
bool checkcol(string player, string **arr, int rowsize);
bool checkdia(string player, string **arr, int rowsize);
bool checkinvdia(string player, string **arr, int rowsize);

void letsDance();

//AI Tactics declaration
void AI_DEF();
void AI_ATT();
void AI_NRML();

//Code -------------------------------------------------------
int main() {
	system("Color B");
	chooseSize();

	gamemode();
	if (choice == "1") {

		decidePlayer();
		PlaySound(TEXT("mario_08.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
		setTable();
		while (full <= (tablesize*tablesize)) {

			if (playfirst == "AI") {
				playfirst = "blabla";
				goto AI;
				PlaySound(TEXT("mario_6.wav"), NULL, SND_ASYNC);
			}


			if (full == (tablesize*tablesize)) {
				if (check(AI, table, tablesize) == true)
				{
					show();
					cout << "AI Won\n"; PlaySound(TEXT("mario_6.wav"), NULL, SND_SYNC);
					break;
				}
				else if (check(HI, table, tablesize) == true) {
					show();
					cout << "Human Won\n"; PlaySound(TEXT("mario_13.wav"), NULL, SND_SYNC);
					break;
				}
				else
				{
					show();
					cout << "It's a draw\n"; PlaySound(TEXT("mario_10.wav"), NULL, SND_SYNC);
					break;
				}
			}

			AImove = false;

			show();
			cout << "Last play: " << last_play << endl;


			enter();
		AI:
			if (check(HI, table, tablesize) == true)
			{
				show();
				cout << "Human won\n"; PlaySound(TEXT("mario_13.wav"), NULL, SND_SYNC);
				cout << "Win play: " << last_play << endl;
				break;
			}
			if (AImove == false)
				AI_ATT();
			if (AImove == false)
				AI_DEF();
			if (AImove == false && full < (tablesize*tablesize))
				AI_NRML();



			if (check(AI, table, tablesize) == true)
			{
				show();
				cout << "Computer won" << endl;
				PlaySound(TEXT("mario_6.wav"), NULL, SND_ASYNC);
				cout << "Win play: " << last_play << endl;
				break;
			}
		}
	}
	else {
		bool once = false;
		while (full <= (tablesize*tablesize)) {
			if (once == false)
			{
				PlaySound(TEXT("mario_08.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
				once = true;
			}
			currentP = HI;
			show();
			enter();
			if (check(currentP, table, tablesize) == true)
			{
				show();
				if (currentP == "O") {
					cout << "Player O Won\n"; PlaySound(TEXT("mario_13.wav"), NULL, SND_SYNC);
				}
				else {
					cout << "Player X Won\n"; PlaySound(TEXT("mario_13.wav"), NULL, SND_SYNC);
				}
				break;
			}
			changePlayer();
		}
	}
	isRepeat();
	for (int i = 0; i < tablesize; i++)
		delete[] table[i];
	delete[] table;
}

void setTable() {
	int m = 1;
	for (int i = 0; i < tablesize; i++)
	{
		for (int z = 0; z < tablesize; z++)
		{
			table[i][z] = to_string(m);
			m++;
		}
	}
}

void show() {
	cout << "Endless Possibilities Team | O6U\n_________________________________\n\n";

	cout << "\t\t\t\t+---------------+";

	for (int length = 0; length < (tablesize - 1); length++)
	{
		cout << "---------------+";
	}

	cout << endl;

	for (int row = 0; row < tablesize; row++)
	{

		cout << "\t\t\t";
		for (int col = 0; col < tablesize; col++)
		{
			cout << "\t|\t" << table[row][col];
		}
		cout << "\t|" << endl;

		cout << "\t\t\t\t+---------------+";

		for (int length = 0; length < (tablesize - 1); length++)
		{
			cout << "---------------+";
		}

		cout << endl;

	}

	if (choice == "2") {
		if (currentP == "O")
			cout << "Player O turn\n";
		else
			cout << "Player X turn\n";
	}
}

void enter() {
	string x;
	cout << "Enter a place to play: ";
	getline(cin, x);
	emptyPlace(x);
}

void emptyPlace(string x) {
	for (int i = 0; i < tablesize; i++)
	{
		for (int z = 0; z < tablesize; z++)
		{
			if (table[i][z] == x) {
				last_play = table[i][z];
				table[i][z] = HI;
				system("cls");
				full++;
				return;
			}
		}
	}
	system("cls");
	show();
	if (full > 1)
		cout << "Enter another place!\n";
	enter();
}

void gamemode() {

	cout << "Endless Possibilities Team | O6U\n_________________________________\n\n";
	cout << "Your prefered gamemode is:\n";
	cout << "1. Player vs AI\n";
	cout << "2. Player 1 vs Player 2\n";
	cin >> choice;

	if (choice != "1" && choice != "2")
		gamemode();
}

void changePlayer() {
	if (HI == "O")
		HI = "X"; // P2
	else
		HI = "O"; // P1
}

void resetPlayer() {
	HI = "O";
}

void restart() {
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
bool check(string player, string **arr, int rowsize) {

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

bool checkrow(string player, string **arr, int rowsize) {

	int winCounter = 0;

	for (int i = 0; i < tablesize; i++)
	{
		for (int z = 0; z < tablesize; z++)
		{
			if (table[i][z] == player)
				winCounter++;
		}
		if (winCounter == tablesize)
			return true;
		else
			winCounter = 0;
	}

	return false;
}

bool checkcol(string player, string **arr, int rowsize) {

	int winCounter = 0;

	for (int i = 0; i < tablesize; i++)
	{
		for (int z = 0; z < tablesize; z++)
		{
			if (table[z][i] == player)
				winCounter++;
		}
		if (winCounter == tablesize)
			return true;
		else
			winCounter = 0;
	}

	return false;
}

bool checkdia(string player, string **arr, int rowsize) {

	int winCounter = 0;

	for (int i = 0; i < tablesize; i++)
	{
		for (int z = 0; z < tablesize; z++)
		{
			if (table[z][z] == player)
				winCounter++;
		}

		if (winCounter == tablesize)
			return true;
		else
			winCounter = 0;
	}

	return false;
}

bool checkinvdia(string player, string **arr, int rowsize) {

	int winCounter = 0;

	for (int i = 0; i < tablesize;)
	{
		for (int z = tablesize - 1; z > -1; z--, i++)
		{
			if (table[i][z] == player)
				winCounter++;
		}

		if (winCounter == tablesize)
			return true;
		else
			winCounter = 0;
	}

	return false;
}

//- -AI
void AI_NRML() {
	int ind = 0; // This is the index of randarray
	int tmpsize, x;
	tmpsize = (tablesize*tablesize) - full; // Size of array will decrease by 1 each round
	randarray = new string[tmpsize]; // Dynamic array which will contain only the empty places only
	for (int i = 0; i < tablesize; i++) { // This loop will fill randarray with only the empty places
		for (int k = 0; k < tablesize; k++) {
			if (table[i][k] != "X" && table[i][k] != "O") {

				randarray[ind] = table[i][k];
				ind++;
			}
		}
	}
	ind = 0; // Reseting index value
	show();
	cout << "Thinking ..." << endl; // Just for UI
	Sleep(1000);
	system("CLS");
	srand((unsigned int)time(NULL)); // Change the odds every time
	x = ((rand() % tmpsize)); // Generate random number between 0 and the size of randarray and store it in x
	for (int i = 0; i < tablesize; i++)
	{
		for (int z = 0; z < tablesize; z++)
		{
			if (randarray[x] == table[i][z])
			{
				last_play = table[i][z];
				table[i][z] = AI;
				AImove = true;
				full++;
				return;
			}
		}
	}

	AI_NRML();
	delete[] randarray;
}

void AI_DEF() {

	string h;

	for (int i = 0; i < tablesize; i++)
	{
		for (int z = 0; z < tablesize; z++)
		{
			if (table[i][z] != AI && table[i][z] != HI) {
				h = table[i][z];
				table[i][z] = HI;

				if (check(HI, table, tablesize) == true)
				{
					last_play = h;
					table[i][z] = AI;
					AImove = true;
					full++;
					return;
				}
				else
					table[i][z] = h;
			}
		}
	}
}

void AI_ATT() {

	string h;

	for (int i = 0; i < tablesize; i++)
	{
		for (int z = 0; z < tablesize; z++)
		{
			if (table[i][z] != AI && table[i][z] != HI) {
				h = table[i][z];
				table[i][z] = AI;

				if (check(AI, table, tablesize) == true)
				{
					last_play = h;
					table[i][z] = AI;
					AImove = true;
					full++;
					return;
				}
				else
					table[i][z] = h;
			}
		}
	}
}

void chooseSize() {
	string k;
	int s;
	system("cls");
	cout << "Endless Possibilities Team | O6U\n_________________________________\n\n";
	cout << "Please enter desired board size : ";
	cin >> s;
	if (s >= 3) {
		tablesize = s;
		table = new string*[s];

		for (int i = 0; i < s; ++i)
			table[i] = new string[s];

		system("cls");
		int g = 1;
		for (int k = 0; k < s; k++)
			for (int j = 0; j < s; j++) {
				table[k][j] = to_string(g);
				++g;
			}
	}
	else
		chooseSize();

}

void isRepeat() {
	char answer;
	cout << "Do you want to play again ? (y/n) : ";
	cin >> answer;
	if (answer == 'Y' || answer == 'y') {
		full = 0; // Reset full value
		system("CLS");
		main();
	}
	else if (answer == 'N' || answer == 'n') {
		cout << "Thanks for using our application, Exiting the game .." << endl;
		exit(0);
	}
	else {
		cout << "You entered wrong choice" << endl;
		isRepeat(); // Repeat the function
	}
}

void decidePlayer() {
	system("CLS");
	cout << "Endless Possibilities Team | O6U\n_________________________________\n\n";
	srand((unsigned int)time(NULL)); // To change the player each time you play the game
	int decidePlayer = (rand() % 2); // The odds are 0 or 1
	if (decidePlayer == 0) // If it was 0 that means human player will start
		playfirst = "human";
	else // If it was 1 that means AI player will start
		playfirst = "AI";
	cout << "There is two players, human and AI!" << endl;
	cout << "Starting player will be decided randomly ";
	// Just to draw "....." as loading each 0.5 second
	for (int i = 0; i < 5; i++) {
		Sleep(500);
		cout << ".";
	}
	Sleep(500);
	cout << "\nWell, " << playfirst << " will start playing... press any key to start the game!";
	_getch();
	system("cls");
}