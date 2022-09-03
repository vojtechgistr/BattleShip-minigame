#include "main.h"

void BattleshipMinigame::enemyDecideWhatShipShot()
{
    if (characterLookingFor == "C") {
        CARRIER--;
        if (CARRIER == 0) {
            playerShips -= 1;
            characterLookingFor = "";
            lastShot[0] = -1;
        }
    }
    else if (characterLookingFor == "B") {
        BATTLESHIP--;
        if (BATTLESHIP == 0) {
            playerShips -= 1;
            characterLookingFor = "";
            lastShot[0] = -1;
        }
    }
    else if (characterLookingFor == "R") {
        CRUISER--;
        if (CRUISER == 0) {
            playerShips -= 1;
            characterLookingFor = "";
            lastShot[0] = -1;
        }
    }
    else if (characterLookingFor == "S") {
        SUBMARINE--;
        if (SUBMARINE == 0) {
            playerShips -= 1;
            characterLookingFor = "";
            lastShot[0] = -1;
        }
    }
    else if (characterLookingFor == "D") {
        DESTROYER--;
        if (DESTROYER == 0) {
            playerShips -= 1;
            characterLookingFor = "";
            lastShot[0] = -1;
        }
    }
}

void BattleshipMinigame::enemyDecideWhatShipShotSetUnknown()
{
    if (characterLookingFor == "C") {
        CARRIER--;
        if (CARRIER == 0) {
            playerShips -= 1;
            characterLookingFor = "";
            lastShot[0] = -1;
            shotDirection = UNKNOWN;
        }
    }
    else if (characterLookingFor == "B") {
        BATTLESHIP--;
        if (BATTLESHIP == 0) {
            playerShips -= 1;
            characterLookingFor = "";
            lastShot[0] = -1;
            shotDirection = UNKNOWN;
        }
    }
    else if (characterLookingFor == "R") {
        CRUISER--;
        if (CRUISER == 0) {
            playerShips -= 1;
            characterLookingFor = "";
            lastShot[0] = -1;
            shotDirection = UNKNOWN;
        }
    }
    else if (characterLookingFor == "S") {
        SUBMARINE--;
        if (SUBMARINE == 0) {
            playerShips -= 1;
            characterLookingFor = "";
            lastShot[0] = -1;
            shotDirection = UNKNOWN;
        }
    }
    else if (characterLookingFor == "D") {
        DESTROYER--;
        if (DESTROYER == 0) {
            playerShips -= 1;
            characterLookingFor = "";
            lastShot[0] = -1;
            shotDirection = UNKNOWN;
        }
    }
}

void BattleshipMinigame::playerShooting()
{
    char rowChar, columnChar;
    int row, column;

    while (whoIsShooting == PLAYER)
    {
        std::cout << "Row [0-9]:";
        SET_CONSOLE_CHARACTER_BLUE
        std::cin >> rowChar;

        SET_CONSOLE_CHARACTER_GRAY
        std::cout << "\n";

        if (isalpha(rowChar)) row = tolower(rowChar) - 97;
        else row = rowChar - 48;

        if (row >= 0 && row <= 9)
        {
            std::cout << "Column [A-J]:";
            SET_CONSOLE_CHARACTER_BLUE
            std::cin >> columnChar;

            SET_CONSOLE_CHARACTER_GRAY
            std::cout << "\n";

            if (isalpha(columnChar)) column = tolower(columnChar) - 97;
            else column = columnChar - 48;

            if (column >= 0 && column <= 9)
            {
                std::string character = enemyBoard[row][column];

                if (character != xchar && character != "X")
                {
                    if (character == "C" || character == "B" || character == "R" || character == "S" || character == "D")
                    {
                        enemyBoard[row][column] = "X";
                        if (character == "C")
                        {
                            enemyCARRIER--;
                            if (enemyCARRIER == 0) enemyShips -= 1;
                        }
                        else if (character == "B")
                        {
                            enemyBATTLESHIP--;
                            if (enemyBATTLESHIP == 0) enemyShips -= 1;
                        }
                        else if (character == "R")
                        {
                            enemyCRUISER--;
                            if (enemyCRUISER == 0) enemyShips -= 1;
                        }
                        else if (character == "S")
                        {
                            enemySUBMARINE--;
                            if (enemySUBMARINE == 0) enemyShips -= 1;
                        }
                        else if (character == "D")
                        {
                            enemyDESTROYER--;
                            if (enemyDESTROYER == 0) enemyShips -= 1;
                        }

                    }
                    else enemyBoard[row][column] = xchar;

                    clearScreen();
                    updateBoard();
                    printControls();
                    whoIsShooting = ENEMY;

                    if (enemyShips != 0) return;
                    else if (enemyShips == 0)
                    {
                        printWinner("player");
                        return;
                    }
                }
            }
        }
    }
};

void BattleshipMinigame::enemyShooting() {
    int row;
    int column;
    unsigned short int tries = 0;

    if (lastShot[0] == -1) {
        while (whoIsShooting == ENEMY) {
            row = random(0, 9);
            column = random(0, 9);

            std::string character = playerBoard[row][column];
            if (character != xchar && character != "X")
            {
                if (character == "C" || character == "B" || character == "R" || character == "S" || character == "D")
                {
                    playerBoard[row][column] = "X";

                    if (character == "C")
                    {
                        CARRIER--;
                        if (CARRIER == 0)
                        {
                            playerShips -= 1;
                            characterLookingFor = "";
                            lastShot[0] = -1;
                            lastShot[1] = -1;
                        }
                        else
                        {
                            characterLookingFor = "C";
                            lastShot[0] = row;
                            lastShot[1] = column;
                        }
                    }
                    else if (character == "B")
                    {
                        BATTLESHIP--;
                        if (BATTLESHIP == 0)
                        {
                            playerShips -= 1;
                            characterLookingFor = "";
                            lastShot[0] = -1;
                            lastShot[1] = -1;
                        }
                        else
                        {
                            characterLookingFor = "B";
                            lastShot[0] = row;
                            lastShot[1] = column;
                        }
                    }
                    else if (character == "R")
                    {
                        CRUISER--;
                        if (CRUISER == 0)
                        {
                            playerShips -= 1;
                            characterLookingFor = "";
                            lastShot[0] = -1;
                            lastShot[1] = -1;
                        }
                        else
                        {
                            characterLookingFor = "R";
                            lastShot[0] = row;
                            lastShot[1] = column;
                        }
                    }
                    else if (character == "S")
                    {
                        SUBMARINE--;
                        if (SUBMARINE == 0) {
                            playerShips -= 1;
                            characterLookingFor = "";
                            lastShot[0] = -1;
                            lastShot[1] = -1;
                        }
                        else {
                            characterLookingFor = "S";
                            lastShot[0] = row;
                            lastShot[1] = column;
                        }
                    }
                    else if (character == "D") {
                        DESTROYER--;
                        if (DESTROYER == 0) {
                            playerShips -= 1;
                            characterLookingFor = "";
                            lastShot[0] = -1;
                            lastShot[1] = -1;
                        }
                        else {
                            characterLookingFor = "D";
                            lastShot[0] = row;
                            lastShot[1] = column;
                        }
                    }
                }
                else playerBoard[row][column] = xchar;

                updateBoard();
                printControls();

                whoIsShooting = PLAYER;

                if (playerShips != 0) return;
                else {
                    printWinner("enemy");
                    return;
                }
            }
        }
    }
    else {
        row = lastShot[0];
        column = lastShot[1];

        while (whoIsShooting == ENEMY)
        {
            if (shotDirection == UNKNOWN)
            {
                if (row - 1 > -1 && playerBoard[row - 1][column] != "X" && playerBoard[row - 1][column] != xchar)
                {
                    if (playerBoard[row - 1][column] == characterLookingFor)
                    {
                        enemyDecideWhatShipShot();

                        playerBoard[row - 1][column] = "X";

                        if (row - 1 <= 0) shotDirection = VERTICAL_DOWN;
                        else
                        {
                            shotDirection = VERTICAL_UP;
                            lastShot[0] = row - 1;
                        }

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0)
                        {
                            printWinner("enemy");
                            return;
                        }

                    }
                    else if (playerBoard[row - 1][column] == dot)
                    {
                        playerBoard[row - 1][column] = xchar;

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0)
                        {
                            printWinner("enemy");
                            return;
                        }
                    }
                }

                if (row + 1 < 10 && playerBoard[row + 1][column] != "X" && playerBoard[row + 1][column] != xchar)
                {
                    if (playerBoard[row + 1][column] == characterLookingFor)
                    {
                        enemyDecideWhatShipShot();

                        playerBoard[row + 1][column] = "X";

                        if (row + 1 >= 9) shotDirection = VERTICAL_UP;
                        else
                        {
                            shotDirection = VERTICAL_DOWN;
                            lastShot[0] = row + 1;
                        }

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0)
                        {
                            printWinner("enemy");
                            return;
                        }
                    }
                    else if (playerBoard[row + 1][column] == dot)
                    {
                        playerBoard[row + 1][column] = xchar;

                        updateBoard();
                        printControls();
                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0) 
                        {
                            printWinner("enemy");
                            return;
                        }
                    }
                }

                if (column - 1 > -1 && playerBoard[row][column - 1] != "X" && playerBoard[row][column - 1] != xchar)
                {
                    if (playerBoard[row][column - 1] == characterLookingFor)
                    {
                        
                        enemyDecideWhatShipShot();

                        playerBoard[row][column - 1] = "X";

                        if (column - 1 <= 0) shotDirection = HORIZONTAL_RIGHT;
                        else
                        {
                            shotDirection = HORIZONTAL_LEFT;
                            lastShot[1] = column - 1;
                        }

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0)
                        {
                            printWinner("enemy");
                            return;
                        }

                    }
                    else if (playerBoard[row][column - 1] == dot)
                    {
                        playerBoard[row][column - 1] = xchar;

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0)
                        {
                            printWinner("enemy");
                            return;
                        }
                    }
                }

                if (column + 1 < 10 && playerBoard[row][column + 1] != "X" && playerBoard[row][column + 1] != xchar) {
                    if (playerBoard[row][column + 1] == characterLookingFor)
                    {
                        enemyDecideWhatShipShot();

                        playerBoard[row][column + 1] = "X";

                        if (column + 1 >= 9) shotDirection = HORIZONTAL_LEFT;
                        else
                        {
                            shotDirection = HORIZONTAL_RIGHT;
                            lastShot[1] = column + 1;
                        }

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0)
                        {
                            printWinner("enemy");
                            return;
                        }

                    }
                    else if (playerBoard[row][column + 1] == dot)
                    {
                        playerBoard[row][column + 1] = xchar;

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0)
                        {
                            printWinner("enemy");
                            return;
                        }
                    }
                }

            }
            else if (shotDirection == VERTICAL_UP)
            {
                if (row - 1 > -1 && playerBoard[row - 1][column] != "X" && playerBoard[row - 1][column] != xchar)
                {
                    if (playerBoard[row - 1][column] == characterLookingFor)
                    {
                        enemyDecideWhatShipShotSetUnknown();

                        playerBoard[row - 1][column] = "X";

                        if (shotDirection != UNKNOWN)
                        {
                            if (row - 1 <= 0) shotDirection = VERTICAL_DOWN;
                            else
                            {
                                shotDirection = VERTICAL_UP;
                                lastShot[0] = row - 1;
                            }
                        }

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0) {
                            printWinner("enemy");
                            return;
                        }

                    }
                    else if (playerBoard[row - 1][column] == dot)
                    {
                        playerBoard[row - 1][column] = xchar;

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0)
                        {
                            printWinner("enemy");
                            return;
                        }
                    }
                    else shotDirection = VERTICAL_DOWN;

                }
                else
                {
                    if (row - 1 > -1 && playerBoard[row - 1][column] == "X")
                    {
                        while (row - 1 > -1 && playerBoard[row - 1][column] == "X")
                        {
                            row -= 1;
                        }
                        lastShot[0] = row;
                    }
                    else shotDirection = VERTICAL_DOWN;
                }

            }
            else if (shotDirection == VERTICAL_DOWN)
{
                if (row + 1 < 10 && playerBoard[row + 1][column] != "X" && playerBoard[row + 1][column] != xchar)
                {
                    if (playerBoard[row + 1][column] == characterLookingFor)
                    {
                        enemyDecideWhatShipShotSetUnknown();

                        playerBoard[row + 1][column] = "X";
                        if (shotDirection != UNKNOWN)
                        {
                            if (row + 1 >= 9) shotDirection = VERTICAL_UP;
                            else
                            {
                                shotDirection = VERTICAL_DOWN;
                                lastShot[0] = row + 1;
                            }
                        }

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0)
                        {
                            printWinner("enemy");
                            return;
                        }

                    }
                    else if (playerBoard[row + 1][column] == dot)
                    {
                        playerBoard[row + 1][column] = xchar;

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0)
                        {
                            printWinner("enemy");
                            return;
                        }
                    }
                    else shotDirection = VERTICAL_UP;

                }
                else
                {
                    if (row + 1 < 10 && playerBoard[row + 1][column] == "X")
                    {
                        while (row + 1 < 10 && playerBoard[row + 1][column] == "X")
                        {
                            row += 1;
                        }
                        lastShot[0] = row;
                    }
                    else shotDirection = VERTICAL_UP;
                }

            }
            else if (shotDirection == HORIZONTAL_LEFT)
{
                if (column - 1 > -1 && playerBoard[row][column - 1] != "X" && playerBoard[row][column - 1] != xchar)
                {
                    if (playerBoard[row][column - 1] == characterLookingFor)
                    {
                        enemyDecideWhatShipShotSetUnknown();

                        playerBoard[row][column - 1] = "X";
                        if (shotDirection != UNKNOWN)
                        {
                            if (column - 1 <= 0) shotDirection = HORIZONTAL_RIGHT;
                            else
                            {
                                shotDirection = HORIZONTAL_LEFT;
                                lastShot[1] = column - 1;
                            }
                        }

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0)
                        {
                            printWinner("enemy");
                            return;
                        }

                    }
                    else if (playerBoard[row][column - 1] == dot)
                    {
                        playerBoard[row][column - 1] = xchar;

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0)
                        {
                            printWinner("enemy");
                            return;
                        }
                    }
                    else shotDirection = HORIZONTAL_RIGHT;

                }
                else
                {
                    if (column - 1 > -1 && playerBoard[row][column - 1] == "X")
                    {
                        while (column - 1 > -1 && playerBoard[row][column - 1] == "X")
                        {
                            column -= 1;
                        }
                        lastShot[1] = column;
                    }
                    else shotDirection = HORIZONTAL_RIGHT;
                }

            }
            else if (shotDirection == HORIZONTAL_RIGHT)
            {
                if (column + 1 < 10 && playerBoard[row][column + 1] != "X" && playerBoard[row][column + 1] != xchar) 
                {
                    if (playerBoard[row][column + 1] == characterLookingFor)
                    {
                        enemyDecideWhatShipShotSetUnknown();

                        playerBoard[row][column + 1] = "X";
                        if (shotDirection != UNKNOWN)
                        {
                            if (column + 1 >= 9) shotDirection = HORIZONTAL_LEFT;
                            else
                            {
                                shotDirection = HORIZONTAL_RIGHT;
                                lastShot[1] = column + 1;
                            }
                        }

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0)
                        {
                            printWinner("enemy");
                            return;
                        }

                    }
                    else if (playerBoard[row][column + 1] == dot)
                    {
                        playerBoard[row][column + 1] = xchar;

                        updateBoard();
                        printControls();

                        whoIsShooting = PLAYER;

                        if (playerShips != 0) return;
                        else if (playerShips == 0)
                        {
                            printWinner("enemy");
                            return;
                        }
                    }
                    else shotDirection = HORIZONTAL_LEFT;

                }
                else
                {
                    if (column + 1 < 10 && playerBoard[row][column + 1] == "X")
                    {
                        while (column + 1 < 10 && playerBoard[row][column + 1] == "X")
                        {
                            column += 1;
                        }
                        lastShot[1] = column;
                    }
                    else shotDirection = HORIZONTAL_LEFT;
                }

            }

            if (tries >= 10)
            {
                characterLookingFor = "";
                lastShot[0] = -1;
                shotDirection = UNKNOWN;

                enemyShooting();
                return;
            }

            else tries++;
        }
    }



};

void BattleshipMinigame::startShootingPhase() {
    while (true) {
        if (whoIsShooting == PLAYER) playerShooting();
        else if (whoIsShooting == ENEMY) enemyShooting();
        else if (whoIsShooting == NOONE) return;
    }
}