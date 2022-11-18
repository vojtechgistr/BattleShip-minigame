#include "main.h"
#include <chrono>
#include <random>

void BattleshipMinigame::start()
{
    createBoard();
}

// test case
int testyawdwad = 0;

void BattleshipMinigame::clearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    // Get the number of cells in the current buffer
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire buffer with spaces
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    // Fill the entire buffer with the current colors and attributes
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    // Move the cursor home
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

int BattleshipMinigame::random(int min, int max)
{
    std::random_device rd;
    // Create random seed
    std::mt19937::result_type seed = rd() ^ (
        (std::mt19937::result_type)
        std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
            ).count() +
        (std::mt19937::result_type)
        std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
            ).count());

    // Set random seed for random function
    srand(seed);
    // Return random number based on min & max value
    return min + (rand() % (max - min + 1));
}

void BattleshipMinigame::removeCharsFromArray(const std::string& character) {
    for (auto& i : enemyBoard) {
        for (auto& j : i) {
            if (j == character) j = dot;
        }
    }
};

void BattleshipMinigame::printUpperText(const unsigned int& showTitle) {

    if (showTitle == 1)
    {
        std::cout << "     _______   ________   _________  _________  __       ______       ______   ___   ___    ________  ______    \n"
                "    /_______/\\ /_______/\\ /________/\\/________/\\/_/\\     /_____/\\     /_____/\\ /__/\\ /__/\\  /_______/\\/_____/\\   \n"
                "    \\::: _  \\ \\\\::: _  \\ \\\\__.::.__\\/\\__.::.__\\/\\:\\ \\    \\::::_\\/_    \\::::_\\/_\\::\\ \\\\  \\ \\ \\__.::._\\/\\:::_ \\ \\  \n"
                "     \\::(_)  \\/_\\::(_)  \\ \\  \\::\\ \\     \\::\\ \\   \\:\\ \\    \\:\\/___/\\    \\:\\/___/\\\\::\\/_\\ .\\ \\   \\::\\ \\  \\:(_) \\ \\ \n"
                "      \\::  _  \\ \\\\:: __  \\ \\  \\::\\ \\     \\::\\ \\   \\:\\ \\____\\::___\\/_    \\_::._\\:\\\\:: ___::\\ \\  _\\::\\ \\__\\: ___\\/ \n"
                "       \\::(_)  \\ \\\\:.\\ \\  \\ \\  \\::\\ \\     \\::\\ \\   \\:\\/___/\\\\:\\____/\\     /____\\:\\\\: \\ \\\\::\\ \\/__\\::\\__/\\\\ \\ \\   \n"
                "        \\_______\\/ \\__\\/\\__\\/   \\__\\/      \\__\\/    \\_____\\/ \\_____\\/     \\_____\\/ \\__\\/ \\::\\/\\________\\/ \\_\\/   \n"
                "\n\n----------------- ";
    }
    
    SET_CONSOLE_CHARACTER_WHITE
    std::cout << "YOUR BOARD";

    SET_CONSOLE_CHARACTER_GRAY
    std::cout << " ------------------                        ------------------ ";

    SET_CONSOLE_CHARACTER_WHITE
    std::cout << "ENEMY BOARD";

    SET_CONSOLE_CHARACTER_GRAY
    std::cout << " ----------------\n|";

    SET_CONSOLE_CHARACTER_DARKGREY
    std::cout << "      A   B   C   D   E   F   G   H   I   J  ";

    SET_CONSOLE_CHARACTER_GRAY
    std::cout << "|                        |";
    SET_CONSOLE_CHARACTER_DARKGREY
    std::cout << "      A   B   C   D   E   F   G   H   I   J  ";
    SET_CONSOLE_CHARACTER_GRAY
    std::cout << "|\n|---------------------------------------------|                        |---------------------------------------------|\n";
}


void BattleshipMinigame::createBoard()
{
    printUpperText();

    for (unsigned row = 0; row < 10; row++)
    {
        std::cout << "| ";
        SET_CONSOLE_CHARACTER_DARKGREY
        std::cout << row;
        SET_CONSOLE_CHARACTER_GRAY
        std::cout << " |";

        // player board
        for (unsigned column = 0; column < 10; column++)
        {
            playerBoard[row][column] = dot;
            if (row == lastCursorPosition[0] && column == lastCursorPosition[1])
            {
                std::cout << "  " << square << " ";
            }
            else
            {
                std::cout << "  " << dot << " ";
            }
        }

        std::cout << " |                        | ";
        SET_CONSOLE_CHARACTER_DARKGREY
        std::cout << row;

        SET_CONSOLE_CHARACTER_GRAY
        std::cout << " |";

        // enemy board
        for (unsigned column = 0; column < 10; column++)
        {
            enemyBoard[row][column] = dot;
            std::cout << "  " << dot << " ";
        }
        std::cout << " |\n";
    }

    std::cout << "--------------- BUILDING PHASE ----------------                        --------------- BUILDING PHASE ----------------\n\n";
    generateEnemyShips();
    printControls();

    // key logs
    while (true) {
        if (GetAsyncKeyState(0x41))                         // A - LEFT KEY
        {
            if (lastCursorPosition[1] != 0)
            {
                lastCursorPosition[1] -= 1;
                updateBoard();
                printControls();
            }

        }
        else if (GetAsyncKeyState(0x44))                    // D - RIGHT KEY
        {
            if (lastCursorPosition[1] != 9)
            {
                lastCursorPosition[1] += 1;
                updateBoard();
                printControls();
            }

        }
        else if (GetAsyncKeyState(0x57))                    // W - UP KEY
        {
            if (lastCursorPosition[0] != 0)
            {
                lastCursorPosition[0] -= 1;
                updateBoard();
                printControls();
            }

        }
        else if (GetAsyncKeyState(0x53))                    // S - DOWN KEY
        {
            if (lastCursorPosition[0] != 9)
            {
                lastCursorPosition[0] += 1;
                updateBoard();
                printControls();
            }

        }
        else if (GetAsyncKeyState(0x0D))                    // ENTER KEY
        {
            std::string character = playerBoard[lastCursorPosition[0]][lastCursorPosition[1]];
            if (shipIndex == 0)
            {
                if (character != "C" && canPlaceShip("C"))
                {
                    if (CARRIER == 5) shipIndex++;
                    else
                    {
                        if (character == "B") BATTLESHIP--;
                        else if (character == "R") CRUISER--;
                        else if (character == "S") SUBMARINE--;
                        else if (character == "D") DESTROYER--;

                        playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = "C";

                        updateBoard();
                        printControls();

                        CARRIER++;

                        if (CARRIER == 5) shipIndex++;
                    }
                }

            }
            else if (shipIndex == 1)
            {
                if (character != "B" && canPlaceShip("B"))
                {
                    if (BATTLESHIP == 4) shipIndex++;
                    else
                    {
                        if (character == "C") CARRIER--;
                        else if (character == "R") CRUISER--;
                        else if (character == "S") SUBMARINE--;
                        else if (character == "D") DESTROYER--;

                        playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = "B";

                        updateBoard();
                        printControls();

                        BATTLESHIP++;

                        if (BATTLESHIP == 4) shipIndex++;
                    }
                }

            }
            else if (shipIndex == 2)
            {
                if (character != "R" && canPlaceShip("R"))
                {
                    if (CRUISER == 3) shipIndex++;
                    else
                    {
                        if (character == "C") CARRIER--;
                        else if (character == "B") BATTLESHIP--;
                        else if (character == "S") SUBMARINE--;
                        else if (character == "D") DESTROYER--;

                        playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = "R";

                        updateBoard();
                        printControls();

                        CRUISER++;

                        if (CRUISER == 3) shipIndex++;
                    }
                }

            }
            else if (shipIndex == 3)
            {
                if (character != "S" && canPlaceShip("S"))
                {
                    if (SUBMARINE == 3) shipIndex++;
                    else
                    {
                        if (character == "C") CARRIER--;
                        else if (character == "B") BATTLESHIP--;
                        else if (character == "R") CRUISER--;
                        else if (character == "D") DESTROYER--;

                        playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = "S";

                        updateBoard();
                        printControls();

                        SUBMARINE++;

                        if (SUBMARINE == 3) shipIndex++;
                    }
                }

            }
            else if (shipIndex == 4) {
                if (character != "D" && canPlaceShip("D"))
                {
                    if (DESTROYER == 2) shipIndex = 0;
                    else
                    {
                        if (character == "C") CARRIER--;
                        else if (character == "B") BATTLESHIP--;
                        else if (character == "R") CRUISER--;
                        else if (character == "S") SUBMARINE--;

                        playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = "D";

                        updateBoard();
                        printControls();

                        DESTROYER++;

                        if (DESTROYER == 2) shipIndex = 0;
                    }
                }
            }

        }
        else if (GetAsyncKeyState(VK_BACK))                     // BACKSPACE KEY
        {
            std::string character = playerBoard[lastCursorPosition[0]][lastCursorPosition[1]];
            if (canDeleteLocation(character))
            {
                playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = dot;
                if (character == "C")
                {
                    shipIndex = 0;
                    CARRIER--;
                }
                else if (character == "B")
                {
                    shipIndex = 1;
                    BATTLESHIP--;
                }
                else if (character == "R")
                {
                    shipIndex = 2;
                    CRUISER--;
                }
                else if (character == "S")
                {
                    shipIndex = 3;
                    SUBMARINE--;
                }
                else if (character == "D")
                {
                    shipIndex = 4;
                    DESTROYER--;
                }

                updateBoard();
                printControls();
            }

        }
        else if (GetAsyncKeyState(0x43))                     // C KEY
        {
            shipIndex++;

            if (shipIndex > 4) shipIndex = 0;

            updateBoard();
            printControls();

        }
        else if (GetAsyncKeyState(VK_F2))                   // F2 KEY
        {
            if (CARRIER == 5 && BATTLESHIP == 4 && CRUISER == 3 && SUBMARINE == 3 && DESTROYER == 2)
            {
                gamePhase = SHOOTING;

                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                clearScreen();

                updateBoard();
                printControls();

                startShootingPhase();
                return;
            }
        }
        else if (GetAsyncKeyState(VK_ESCAPE)) return;
        Sleep(100);
    }
}

void BattleshipMinigame::updateBoard()
{
    COORD cur = { 0, 0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

    // Show the title
    printUpperText();

    // Print the rest of the board
    for (int row = 0; row < 10; row++)
    {
        std::cout << "| ";
        SET_CONSOLE_CHARACTER_DARKGREY
        std::cout << row;

        SET_CONSOLE_CHARACTER_GRAY
        std::cout << " |";

        // Print player board half-line
        for (int column = 0; column < 10; column++)
        {
            std::string ship = playerBoard[row][column];

            // Shows current cursor position if game phase is BUILDING
            if (gamePhase == BUILDING && row == lastCursorPosition[0] && column == lastCursorPosition[1])
            {
                if (ship == "C" || ship == "B" || ship == "R" || ship == "S" || ship == "D")
                {
                    SET_CONSOLE_CHARACTER_LIGHTGRAY_BLACK
                    std::cout << "  " << ship << " ";
                }
                else
                {
                    std::cout << "  " << square << " ";
                }
            }
            else
            {
                // Show X marker if the current ship tile is destroyed
                if (ship == "X") 
                {
                    SET_CONSOLE_CHARACTER_RED
                    std::cout << "  X ";
                }
                else if (ship == xchar)
                {
                    std::cout << "  " << xchar << " ";
                }
                else
                {
                    // Change color based on ship type
                    if (ship == "C") SET_CONSOLE_CHARACTER_DARKBLUE_BLACK

                    else if (ship == "B") SET_CONSOLE_CHARACTER_LIGHTBLUE_BLACK

                    else if (ship == "R") SET_CONSOLE_CHARACTER_LIGHTBLUE_WHITE

                    else if (ship == "S") SET_CONSOLE_CHARACTER_BLUE_BLACK

                    else if (ship == "D") SET_CONSOLE_CHARACTER_GREEN_BLACK

                    std::cout << "  " << ship << " ";
                }
            }
            SET_CONSOLE_CHARACTER_GRAY
        }

        std::cout << " |                        | ";

        SET_CONSOLE_CHARACTER_DARKGREY
        std::cout << row;

        SET_CONSOLE_CHARACTER_GRAY
        std::cout << " |";

        // Print enemy board half-line
        for (int column = 0; column < 10; column++)
        {
            // If game phase is SHOOTING, show all destroyed tiles, else show DOTs
            if (gamePhase == SHOOTING)
            {
                std::string ship = enemyBoard[row][column];

                // Show X marker if the current ship tile is destroyed
                if (ship == "X")
                {
                    SET_CONSOLE_CHARACTER_RED
                    std::cout << "  X ";
                    SET_CONSOLE_CHARACTER_GRAY
                }
                else if (ship == xchar) std::cout << "  " << xchar << " ";
                else std::cout << "  " << dot << " ";

            }
            else std::cout << "  " << dot << " ";
        }

        std::cout << " |\n";
    }

    // Show BUILDING PHASE text if BUILDING phase, else show number of SHIPS LEFT
    if (gamePhase == BUILDING)
    {
        std::cout << "--------------- BUILDING PHASE ----------------                        -----------------------------------------------\n\n";
    }
    else
    {
        std::cout << "----------------- ";
        SET_CONSOLE_CHARACTER_WHITE
        std::cout << playerShips;

        SET_CONSOLE_CHARACTER_GRAY
        std::cout << " SHIPS LEFT ----------------";
        std::cout << "                        ----------------- ";

        SET_CONSOLE_CHARACTER_WHITE
        std::cout << enemyShips;

        SET_CONSOLE_CHARACTER_GRAY
        std::cout << " SHIPS LEFT ----------------\n\n";
    }
};

void BattleshipMinigame::printWinner(const std::string& winner)
{
    clearScreen();

    if (winner == "player")
    {
        std::cout << "$$$$$$$\\  $$\\                                                             $$\\                     \n"
            "$$  __$$\\ $$ |                                                            \\__|                    \n"
            "$$ |  $$ |$$ | $$$$$$\\  $$\\   $$\\  $$$$$$\\   $$$$$$\\        $$\\  $$\\  $$\\ $$\\ $$$$$$$\\   $$$$$$$\\ \n"
            "$$$$$$$  |$$ | \\____$$\\ $$ |  $$ |$$  __$$\\ $$  __$$\\       $$ | $$ | $$ |$$ |$$  __$$\\ $$  _____|\n"
            "$$  ____/ $$ | $$$$$$$ |$$ |  $$ |$$$$$$$$ |$$ |  \\__|      $$ | $$ | $$ |$$ |$$ |  $$ |\\$$$$$$\\  \n"
            "$$ |      $$ |$$  __$$ |$$ |  $$ |$$   ____|$$ |            $$ | $$ | $$ |$$ |$$ |  $$ | \\____$$\\ \n"
            "$$ |      $$ |\\$$$$$$$ |\\$$$$$$$ |\\$$$$$$$\\ $$ |            \\$$$$$\\$$$$  |$$ |$$ |  $$ |$$$$$$$  |\n"
            "\\__|      \\__| \\_______| \\____$$ | \\_______|\\__|             \\_____\\____/ \\__|\\__|  \\__|\\_______/ \n"
            "                        $$\\   $$ |                                                                \n"
            "                        \\$$$$$$  |                                                                \n"
            "                         \\______/                                                                 \n\n----------------- ";

    }
    else if (winner == "enemy")
    {
        std::cout << "$$$$$$$$\\                                                                 $$\\                     \n"
            "$$  _____|                                                                \\__|                    \n"
            "$$ |      $$$$$$$\\   $$$$$$\\  $$$$$$\\$$$$\\  $$\\   $$\\       $$\\  $$\\  $$\\ $$\\ $$$$$$$\\   $$$$$$$\\ \n"
            "$$$$$\\    $$  __$$\\ $$  __$$\\ $$  _$$  _$$\\ $$ |  $$ |      $$ | $$ | $$ |$$ |$$  __$$\\ $$  _____|\n"
            "$$  __|   $$ |  $$ |$$$$$$$$ |$$ / $$ / $$ |$$ |  $$ |      $$ | $$ | $$ |$$ |$$ |  $$ |\\$$$$$$\\  \n"
            "$$ |      $$ |  $$ |$$   ____|$$ | $$ | $$ |$$ |  $$ |      $$ | $$ | $$ |$$ |$$ |  $$ | \\____$$\\ \n"
            "$$$$$$$$\\ $$ |  $$ |\\$$$$$$$\\ $$ | $$ | $$ |\\$$$$$$$ |      \\$$$$$\\$$$$  |$$ |$$ |  $$ |$$$$$$$  |\n"
            "\\________|\\__|  \\__| \\_______|\\__| \\__| \\__| \\____$$ |       \\_____\\____/ \\__|\\__|  \\__|\\_______/ \n"
            "                                            $$\\   $$ |                                            \n"
            "                                            \\$$$$$$  |                                            \n"
            "                                             \\______/                                             \n\n----------------- ";
    }

    printUpperText(0);

    for (int row = 0; row < 10; row++)
    {
        std::cout << "| ";
        SET_CONSOLE_CHARACTER_DARKGREY
        std::cout << row;
        SET_CONSOLE_CHARACTER_GRAY
        std::cout << " |";

        // player board
        for (int column = 0; column < 10; column++)
        {
            std::string ship = playerBoard[row][column];
            // Show X marker if the current ship tile is destroyed
            if (ship == "X")
            {
                SET_CONSOLE_CHARACTER_RED
                std::cout << "  X ";
            }
            else if (ship == xchar)
            {
                std::cout << "  " << xchar << " ";
            }
            else
            {
                // Change color based on ship type
                if (ship == "C") SET_CONSOLE_CHARACTER_DARKBLUE_BLACK

                else if (ship == "B") SET_CONSOLE_CHARACTER_LIGHTBLUE_BLACK

                else if (ship == "R") SET_CONSOLE_CHARACTER_LIGHTBLUE_WHITE

                else if (ship == "S") SET_CONSOLE_CHARACTER_BLUE_BLACK

                else if (ship == "D") SET_CONSOLE_CHARACTER_GREEN_BLACK

                std::cout << "  " << ship << " ";
            }

            SET_CONSOLE_CHARACTER_GRAY
        }

        std::cout << " |                        | ";
        SET_CONSOLE_CHARACTER_DARKGREY
        std::cout << row;

        SET_CONSOLE_CHARACTER_GRAY
        std::cout << " |";

        // enemy board
        for (int column = 0; column < 10; column++)
        {
            std::string ship = enemyBoard[row][column];
            // Show X marker if the current ship tile is destroyed
            if (ship == "X")
            {
                SET_CONSOLE_CHARACTER_RED
                std::cout << "  X ";
            }
            else if (ship == xchar)
            {
                std::cout << "  " << xchar << " ";
            }
            else
            {
                // Change color based on ship type
                if (ship == "C") SET_CONSOLE_CHARACTER_DARKBLUE_BLACK

                else if (ship == "B") SET_CONSOLE_CHARACTER_LIGHTBLUE_BLACK

                else if (ship == "R") SET_CONSOLE_CHARACTER_LIGHTBLUE_WHITE

                else if (ship == "S") SET_CONSOLE_CHARACTER_BLUE_BLACK

                else if (ship == "D") SET_CONSOLE_CHARACTER_GREEN_BLACK

                std::cout << "  " << ship << " ";
            }

            SET_CONSOLE_CHARACTER_GRAY
        }
        std::cout << " |\n";
    }

    std::cout << "----------------- ";
    SET_CONSOLE_CHARACTER_WHITE
    std::cout << playerShips;

    SET_CONSOLE_CHARACTER_GRAY
    std::cout << " SHIPS LEFT ----------------";
    std::cout << "                        ----------------- ";

    SET_CONSOLE_CHARACTER_WHITE
    std::cout << enemyShips;

    SET_CONSOLE_CHARACTER_GRAY
    std::cout << " SHIPS LEFT ----------------\n\n";

    gamePhase = END;
    whoIsShooting = NOONE;

}
void BattleshipMinigame::printControls()
{
    if (gamePhase == BUILDING)
    {
        std::cout << "Currently building ship: ";

        SET_CONSOLE_CHARACTER_WHITE
        std::cout << listOfAllShips[shipIndex];

        SET_CONSOLE_CHARACTER_GREEN

        std::cout << "       \n\n"
            "W = UP                     ENTER - PLACE A SHIP\n"
            "S = DOWN                   C - CHANGE TYPE OF A SHIP\n"
            "A = LEFT                   F2 - SAVE BOARD - START GAME\n"
            "D = RIGHT                  ESC - END GAME\n";

        SET_CONSOLE_CHARACTER_GRAY
    }
}
