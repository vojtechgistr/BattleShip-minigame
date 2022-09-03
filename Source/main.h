#pragma once

#include <iostream>
#include <windows.h>
#include <array>

#define square	std::string(1, (char)254)
#define dot	std::string(1, (char)250)
#define xchar	std::string(1, (char)120)

#define SET_CONSOLE_CHARACTER_GRAY			SetConsoleTextAttribute(hConsole, 7);
#define SET_CONSOLE_CHARACTER_DARKGREY			SetConsoleTextAttribute(hConsole, 8);
#define SET_CONSOLE_CHARACTER_BLUE			SetConsoleTextAttribute(hConsole, 9);
#define SET_CONSOLE_CHARACTER_GREEN			SetConsoleTextAttribute(hConsole, 10);
#define SET_CONSOLE_CHARACTER_RED			SetConsoleTextAttribute(hConsole, 12);
#define SET_CONSOLE_CHARACTER_WHITE			SetConsoleTextAttribute(hConsole, 15);

//	    BACKGROUND COLOR _ CHARACTER COLOR 
#define SET_CONSOLE_CHARACTER_DARKBLUE_BLACK				SetConsoleTextAttribute(hConsole, 16);
#define SET_CONSOLE_CHARACTER_LIGHTBLUE_BLACK				SetConsoleTextAttribute(hConsole, 48);
#define SET_CONSOLE_CHARACTER_LIGHTBLUE_WHITE				SetConsoleTextAttribute(hConsole, 63);
#define SET_CONSOLE_CHARACTER_LIGHTGRAY_BLACK				SetConsoleTextAttribute(hConsole, 112);
#define SET_CONSOLE_CHARACTER_BLUE_BLACK				SetConsoleTextAttribute(hConsole, 144);
#define SET_CONSOLE_CHARACTER_GREEN_BLACK				SetConsoleTextAttribute(hConsole, 160);

	
class BattleshipMinigame {

public:
	void start();

protected:
	// Console Handle definition
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Other function definitions
	static void clearScreen();
	static int random(int min, int max);

	void enemyDecideWhatShipShot();
	void enemyDecideWhatShipShotSetUnknown();

	bool canPlaceShip(const std::string& shipIndicator);
	bool canDeleteLocation(const std::string& shipIndicator);
	void checkIfDoesNotExceedBoard(unsigned short int& randomRow, unsigned short int& randomColumn, unsigned short int& randomDirection, unsigned short int& tries, short int& rowIncrement, short int& columnIncrement, unsigned short int& canIncrement);
	void generateEnemyShips();
	void removeCharsFromArray(const std::string& character);

	void playerShooting();
	void enemyShooting();
	void startShootingPhase();

	void printUpperText(const unsigned int& showTitle = 1);
	void createBoard();
	void updateBoard();
	void printControls();
	void printWinner(const std::string& winner);

private:

	// Player & Enemy board declaration
	std::string playerBoard[10][10];
	std::string enemyBoard[10][10];

	enum { PLAYER, ENEMY, NOONE };
	unsigned short int whoIsShooting = PLAYER;

	enum { BUILDING, SHOOTING, END };
	unsigned short int gamePhase = BUILDING;

	// Shoot direction ENUMS for an AI
	enum { UNKNOWN, VERTICAL_UP, VERTICAL_DOWN, HORIZONTAL_RIGHT, HORIZONTAL_LEFT };

	const std::string listOfAllShips[5] = { "CARRIER", "BATTLESHIP", "CRUISER", "SUBMARINE", "DESTROYER" };

	unsigned short int playerShips = 5, enemyShips = 5, shipIndex = 0;

	// Store number of ship parts destroyed
	unsigned short int CARRIER = 0, BATTLESHIP = 0, CRUISER = 0, SUBMARINE = 0, DESTROYER = 0,
		enemyCARRIER = 0, enemyBATTLESHIP = 0, enemyCRUISER = 0, enemySUBMARINE = 0, enemyDESTROYER = 0;

	std::array<int, 2> lastCursorPosition = { 0, 0 };			// [0] = vertical, [1] = horizontal
	std::array<int, 2> lastShot = { -1, -1 };				// Store an enemy shot to the player

	std::string characterLookingFor = "";
	unsigned short int shotDirection = UNKNOWN;				// Store an enemy shot direction

	enum { YES, NO };

};
