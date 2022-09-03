#include "main.h"

bool BattleshipMinigame::canPlaceShip(const std::string& shipIndicator)
{
    /* check if same ship type is around */
    if (lastCursorPosition[0] + 1 <= 9 && playerBoard[lastCursorPosition[0] + 1][lastCursorPosition[1]] == shipIndicator) {
        if ((lastCursorPosition[1] + 1 <= 9 && playerBoard[lastCursorPosition[0] + 1][lastCursorPosition[1] + 1] == shipIndicator) || (lastCursorPosition[1] - 1 >= 0 && playerBoard[lastCursorPosition[0] + 1][lastCursorPosition[1] - 1] == shipIndicator))
            return false; // bad direction
        else return true;

    }
    else if (lastCursorPosition[0] - 1 >= 0 && playerBoard[lastCursorPosition[0] - 1][lastCursorPosition[1]] == shipIndicator) {
        if ((lastCursorPosition[1] + 1 <= 9 && playerBoard[lastCursorPosition[0] - 1][lastCursorPosition[1] + 1] == shipIndicator) || (lastCursorPosition[1] - 1 >= 0 && playerBoard[lastCursorPosition[0] - 1][lastCursorPosition[1] - 1] == shipIndicator))
            return false; // bad direction
        else return true;

    }
    else if (lastCursorPosition[1] + 1 <= 9 && playerBoard[lastCursorPosition[0]][lastCursorPosition[1] + 1] == shipIndicator) {
        if ((lastCursorPosition[0] + 1 <= 9 && playerBoard[lastCursorPosition[0] + 1][lastCursorPosition[1] + 1] == shipIndicator) || (lastCursorPosition[0] - 1 >= 0 && playerBoard[lastCursorPosition[0] - 1][lastCursorPosition[1] + 1] == shipIndicator))
            return false; // bad direction
        else return true;

    }
    else if (lastCursorPosition[1] - 1 >= 0 && playerBoard[lastCursorPosition[0]][lastCursorPosition[1] - 1] == shipIndicator) {
        if ((lastCursorPosition[0] + 1 <= 9 && playerBoard[lastCursorPosition[0] + 1][lastCursorPosition[1] - 1] == shipIndicator) || (lastCursorPosition[0] - 1 >= 0 && playerBoard[lastCursorPosition[0] - 1][lastCursorPosition[1] - 1] == shipIndicator))
            return false; // bad direction
        else return true;
    }

    /* check if ship already exists (somewhere) */
    for (auto& row : playerBoard) {
        for (auto& column : row) {
            if (column == shipIndicator) return false;
        }
    }
    return true;
}

bool BattleshipMinigame::canDeleteLocation(const std::string& shipIndicator)
{
    if (lastCursorPosition[0] != 0 && (playerBoard[lastCursorPosition[0] + 1][lastCursorPosition[1]] == shipIndicator && playerBoard[lastCursorPosition[0] - 1][lastCursorPosition[1]] == shipIndicator)) return false;
    if (lastCursorPosition[1] != 0 && (playerBoard[lastCursorPosition[0]][lastCursorPosition[1] + 1] == shipIndicator && playerBoard[lastCursorPosition[0]][lastCursorPosition[1] - 1] == shipIndicator)) return false;
    return true;
}

void BattleshipMinigame::checkIfDoesNotExceedBoard(unsigned short int& randomRow, unsigned short int& randomColumn, unsigned short int& randomDirection,
    unsigned short int& tries, short int& rowIncrement, short int& columnIncrement, unsigned short int& canIncrement)
{
    if (randomRow + rowIncrement < 0 || randomColumn + columnIncrement < 0 || randomRow + rowIncrement > 9 || randomColumn + columnIncrement > 9)
    {
        if (randomDirection == 0) rowIncrement = -1;
        else if (randomDirection == 1) columnIncrement = -1;

        tries++;
        canIncrement = NO;
    }
}

void BattleshipMinigame::generateEnemyShips()
{
    unsigned short int randomRow = random(0, 9);
    unsigned short int randomColumn = random(0, 9);
    unsigned short int randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal

    short int rowIncrement = 0;
    short int columnIncrement = 0;

    unsigned short int tries = 0;

    unsigned short int canIncrement = YES;

    // CARRIER
    while (enemyCARRIER != 5)
    {
        checkIfDoesNotExceedBoard(randomRow, randomColumn, randomDirection, tries, rowIncrement, columnIncrement, canIncrement);

        std::string character = enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement];
        if (character == "B" || character == "R" || character == "S" || character == "D")
        {
            if (randomDirection == 0) rowIncrement = -1;
            else if (randomDirection == 1) columnIncrement = -1;

            tries++;
            canIncrement = NO;

        }
        else if (character == dot)
        {
            enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement] = "C";
            enemyCARRIER++;
        }

        if (canIncrement == YES)
        {
            if (randomDirection == 0)
            {
                if (rowIncrement > -1) rowIncrement++;
                else rowIncrement--;

            }
            else if (randomDirection == 1)
            {
                if (columnIncrement > -1) columnIncrement++;
                else columnIncrement--;
            }
        }
        else canIncrement = YES;

        if (tries == 10)
        {
            removeCharsFromArray("C");
            enemyCARRIER = 0;
            randomRow = random(0, 9);
            randomColumn = random(0, 9);
            randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
            rowIncrement = 0;
            columnIncrement = 0;
            tries = 0;
        }
    }

    // BATTLESHIP
    randomRow = random(0, 9);
    randomColumn = random(0, 9);
    randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
    rowIncrement = 0;
    columnIncrement = 0;
    tries = 0;

    while (enemyBATTLESHIP != 4)
    {
        checkIfDoesNotExceedBoard(randomRow, randomColumn, randomDirection, tries, rowIncrement, columnIncrement, canIncrement);

        std::string character = enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement];
        if (character == "C" || character == "R" || character == "S" || character == "D")
        {
            if (randomDirection == 0) rowIncrement = -1;
            else if (randomDirection == 1) columnIncrement = -1;
            tries++;
            canIncrement = NO;

        }
        else if (character == dot)
        {
            enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement] = "B";
            enemyBATTLESHIP++;
        }

        if (canIncrement == YES)
        {
            if (randomDirection == 0)
            {
                if (rowIncrement > -1) rowIncrement++;
                else rowIncrement--;

            }
            else if (randomDirection == 1)
            {
                if (columnIncrement > -1) columnIncrement++;
                else columnIncrement--;
            }
        }
        else canIncrement = YES;

        if (tries == 10)
        {
            removeCharsFromArray("B");
            enemyBATTLESHIP = 0;
            randomRow = random(0, 9);
            randomColumn = random(0, 9);
            randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
            rowIncrement = 0;
            columnIncrement = 0;
            tries = 0;
        }
    }

    // CRUISER
    randomRow = random(0, 9);
    randomColumn = random(0, 9);
    randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
    rowIncrement = 0;
    columnIncrement = 0;
    tries = 0;

    while (enemyCRUISER != 3)
    {
        checkIfDoesNotExceedBoard(randomRow, randomColumn, randomDirection, tries, rowIncrement, columnIncrement, canIncrement);

        std::string character = enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement];
        if (character == "B" || character == "C" || character == "S" || character == "D")
        {
            if (randomDirection == 0) rowIncrement = -1;
            else if (randomDirection == 1) columnIncrement = -1;
            tries++;
            canIncrement = NO;

        }
        else if (character == dot)
        {
            enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement] = "R";
            enemyCRUISER++;
        }

        if (canIncrement == YES)
        {
            if (randomDirection == 0)
            {
                if (rowIncrement > -1) rowIncrement++;
                else rowIncrement--;

            }
            else if (randomDirection == 1)
            {
                if (columnIncrement > -1) columnIncrement++;
                else columnIncrement--;
            }
        }
        else canIncrement = YES;

        if (tries == 10)
        {
            removeCharsFromArray("R");
            enemyCRUISER = 0;
            randomRow = random(0, 9);
            randomColumn = random(0, 9);
            randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
            rowIncrement = 0;
            columnIncrement = 0;
            tries = 0;
        }
    }

    // SUBMARINE
    randomRow = random(0, 9);
    randomColumn = random(0, 9);
    randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
    rowIncrement = 0;
    columnIncrement = 0;
    tries = 0;

    while (enemySUBMARINE != 3)
    {
        checkIfDoesNotExceedBoard(randomRow, randomColumn, randomDirection, tries, rowIncrement, columnIncrement, canIncrement);

        std::string character = enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement];
        if (character == "B" || character == "R" || character == "C" || character == "D")
        {
            if (randomDirection == 0) rowIncrement = -1;
            else if (randomDirection == 1) columnIncrement = -1;
            tries++;
            canIncrement = NO;

        }
        else if (character == dot)
        {
            enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement] = "S";
            enemySUBMARINE++;
        }

        if (canIncrement == YES)
        {
            if (randomDirection == 0)
            {
                if (rowIncrement > -1) rowIncrement++;
                else rowIncrement--;

            }
            else if (randomDirection == 1)
            {
                if (columnIncrement > -1) columnIncrement++;
                else columnIncrement--;
            }
        }
        else canIncrement = YES;

        if (tries == 10)
        {
            removeCharsFromArray("S");
            enemySUBMARINE = 0;
            randomRow = random(0, 9);
            randomColumn = random(0, 9);
            randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
            rowIncrement = 0;
            columnIncrement = 0;
            tries = 0;
        }
    }

    // DESTROYER
    randomRow = random(0, 9);
    randomColumn = random(0, 9);
    randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
    rowIncrement = 0;
    columnIncrement = 0;
    tries = 0;

    while (enemyDESTROYER != 2)
    {
        checkIfDoesNotExceedBoard(randomRow, randomColumn, randomDirection, tries, rowIncrement, columnIncrement, canIncrement);

        std::string character = enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement];
        if (character == "B" || character == "R" || character == "S" || character == "C")
        {
            if (randomDirection == 0) rowIncrement = -1;
            else if (randomDirection == 1) columnIncrement = -1;
            tries++;
            canIncrement = NO;

        }
        else if (character == dot)
        {
            enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement] = "D";
            enemyDESTROYER++;
        }

        if (canIncrement == YES)
        {
            if (randomDirection == 0)
            {
                if (rowIncrement > -1) rowIncrement++;
                else rowIncrement--;

            }
            else if (randomDirection == 1)
            {
                if (columnIncrement > -1) columnIncrement++;
                else columnIncrement--;
            }
        }
        else canIncrement = YES;

        if (tries == 10)
        {
            removeCharsFromArray("D");
            enemyDESTROYER = 0;
            randomRow = random(0, 9);
            randomColumn = random(0, 9);
            randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
            rowIncrement = 0;
            columnIncrement = 0;
            tries = 0;
        }
    }

};
