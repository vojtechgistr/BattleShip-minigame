#include <iostream>
#include <windows.h>
#include <array>
#include <chrono>
#include <random>
#include <string>
#include <cctype>

#define square string(1, (char)254)
#define dot string(1, (char)250)
#define xchar string(1, (char)120)

using std::cout, std::cin, std::string, std::array;

class BattleShipMinigame {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string playerBoard[10][10] = {};
    string enemyBoard[10][10] = {};
    unsigned short int whoIsShooting = 0;
    unsigned short int gamePhase = 0;
    enum { PLAYER, ENEMY, NOONE };
    enum { BUILDING, SHOOTING, END };
    string listOfAllShips[5] = {"CARRIER", "BATTLESHIP", "CRUISER", "SUBMARINE", "DESTROYER"};
    unsigned short int playerShips = 5, enemyShips = 5, shipIndex = 0;
    unsigned short int CARRIER = 0, BATTLESHIP = 0, CRUISER = 0, SUBMARINE = 0, DESTROYER = 0,
                        enemyCARRIER = 0, enemyBATTLESHIP = 0, enemyCRUISER = 0, enemySUBMARINE = 0, enemyDESTROYER = 0;
    array<int, 2> lastCursorPosition = {0, 0}; // [0] = vertical, [1] = horizontal
public:
    void start() {
        createBoard();
    };

private:
    static void clearScreen() {
        HANDLE                     hStdOut;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD                      count;
        DWORD                      cellCount;
        COORD                      homeCoords = { 0, 0 };

        hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        if (hStdOut == INVALID_HANDLE_VALUE) return;

        /* Get the number of cells in the current buffer */
        if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
        cellCount = csbi.dwSize.X *csbi.dwSize.Y;

        /* Fill the entire buffer with spaces */
        if (!FillConsoleOutputCharacter(
                hStdOut,
                (TCHAR) ' ',
                cellCount,
                homeCoords,
                &count
        )) return;

        /* Fill the entire buffer with the current colors and attributes */
        if (!FillConsoleOutputAttribute(
                hStdOut,
                csbi.wAttributes,
                cellCount,
                homeCoords,
                &count
        )) return;

        /* Move the cursor home */
        SetConsoleCursorPosition( hStdOut, homeCoords );
    };

    static int random(int min, int max) {
        std::random_device rd;
        std::mt19937::result_type seed = rd() ^ (
                (std::mt19937::result_type)
                        std::chrono::duration_cast<std::chrono::seconds>(
                                std::chrono::system_clock::now().time_since_epoch()
                        ).count() +
                (std::mt19937::result_type)
                        std::chrono::duration_cast<std::chrono::microseconds>(
                                std::chrono::high_resolution_clock::now().time_since_epoch()
                        ).count());

        srand(seed);
        return min + (rand() % (max - min + 1));
    }

//    static array<int, 2> indexOf(string array[10][10], string character) // 2D array
//    {
//        for(int i = 0;i<10;i++) {
//            for(int j = 0;j<10;j++){
//                if(array[i][j] == character) {
//                    return {i, j};
//                }
//            }
//        }
//    }

    bool canPlaceShip(const string& shipIndicator) {
//        for(int row = -1;row<2;row++) {
//            for(int column = -1;column<2;column++) {
//                if(((lastCursorPosition[0]-1 > -1 || lastCursorPosition[1]-1 > -1) && (lastCursorPosition[0]+1 < 10 || lastCursorPosition[1]+1 < 10))) {
//                    if(playerBoard[lastCursorPosition[0]+row][lastCursorPosition[1]+column] == shipIndicator) {
//                        /* Checks direction of the ship */
//                        for(int row2 = -1;row2<2;row2++) {
//                            for (int column2 = -1; column2 < 2; column2++) {
//                                if((lastCursorPosition[0]+row+row2 != lastCursorPosition[0] && lastCursorPosition[1]+column+column2 != lastCursorPosition[1]) && ((lastCursorPosition[0]-1 > -1 || lastCursorPosition[1]-1 > -1) && (lastCursorPosition[0]+1 < 10 || lastCursorPosition[1]+1 < 10))) {
//                                    if(playerBoard[lastCursorPosition[0] + row + row2][lastCursorPosition[1] + column + column2] == shipIndicator) return false; // bad direction
//                                }
//                            }
//                        }
//                        return true;
//                    }
//                }
//            }
//        }

        /* check if same ship type is around */
        if(lastCursorPosition[0]+1 <= 9 && playerBoard[lastCursorPosition[0]+1][lastCursorPosition[1]] == shipIndicator) {
            if((lastCursorPosition[1]+1 <= 9 && playerBoard[lastCursorPosition[0]+1][lastCursorPosition[1]+1] == shipIndicator) || (lastCursorPosition[1-1] >= 0 && playerBoard[lastCursorPosition[0]+1][lastCursorPosition[1]-1] == shipIndicator))
                return false; // bad direction
            else return true;

        } else if(lastCursorPosition[0]-1 >= 0 && playerBoard[lastCursorPosition[0]-1][lastCursorPosition[1]] == shipIndicator) {
            if((lastCursorPosition[1]+1 <= 9 && playerBoard[lastCursorPosition[0]-1][lastCursorPosition[1]+1] == shipIndicator) || (lastCursorPosition[1-1] >= 0 && playerBoard[lastCursorPosition[0]-1][lastCursorPosition[1]-1] == shipIndicator))
                return false; // bad direction
            else return true;

        } else if(lastCursorPosition[1]+1 <= 9 && playerBoard[lastCursorPosition[0]][lastCursorPosition[1]+1] == shipIndicator) {
            if((lastCursorPosition[0]+1 <= 9 && playerBoard[lastCursorPosition[0]+1][lastCursorPosition[1]+1] == shipIndicator) || (lastCursorPosition[0]-1 >= 0 && playerBoard[lastCursorPosition[0]-1][lastCursorPosition[1]+1] == shipIndicator))
                return false; // bad direction
            else return true;

        } else if(lastCursorPosition[1]-1 >= 0 && playerBoard[lastCursorPosition[0]][lastCursorPosition[1]-1] == shipIndicator) {
            if((lastCursorPosition[0]+1 <= 9 && playerBoard[lastCursorPosition[0]+1][lastCursorPosition[1]-1] == shipIndicator) || (lastCursorPosition[0]-1 >= 0 && playerBoard[lastCursorPosition[0]-1][lastCursorPosition[1]-1] == shipIndicator))
                return false; // bad direction
            else return true;
        }

        /* check if ship already exists (somewhere) */
        for(auto & row : playerBoard) {
            for(auto & column : row) {
                if(column == shipIndicator) return false;
            }
        }
        return true;
    };

    bool canDeleteLocation(const string& shipIndicator) {
        if(lastCursorPosition[0] != 0 && (playerBoard[lastCursorPosition[0]+1][lastCursorPosition[1]] == shipIndicator && playerBoard[lastCursorPosition[0]-1][lastCursorPosition[1]] == shipIndicator)) return false;
        if(lastCursorPosition[1] != 0 && (playerBoard[lastCursorPosition[0]][lastCursorPosition[1]+1] == shipIndicator && playerBoard[lastCursorPosition[0]][lastCursorPosition[1]-1] == shipIndicator)) return false;
        return true;
    }

    void updateBoard() {
        COORD cur = {0, 0};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
        cout << "     _______   ________   _________  _________  __       ______       ______   ___   ___    ________  ______    \n"
                "    /_______/\\ /_______/\\ /________/\\/________/\\/_/\\     /_____/\\     /_____/\\ /__/\\ /__/\\  /_______/\\/_____/\\   \n"
                "    \\::: _  \\ \\\\::: _  \\ \\\\__.::.__\\/\\__.::.__\\/\\:\\ \\    \\::::_\\/_    \\::::_\\/_\\::\\ \\\\  \\ \\ \\__.::._\\/\\:::_ \\ \\  \n"
                "     \\::(_)  \\/_\\::(_)  \\ \\  \\::\\ \\     \\::\\ \\   \\:\\ \\    \\:\\/___/\\    \\:\\/___/\\\\::\\/_\\ .\\ \\   \\::\\ \\  \\:(_) \\ \\ \n"
                "      \\::  _  \\ \\\\:: __  \\ \\  \\::\\ \\     \\::\\ \\   \\:\\ \\____\\::___\\/_    \\_::._\\:\\\\:: ___::\\ \\  _\\::\\ \\__\\: ___\\/ \n"
                "       \\::(_)  \\ \\\\:.\\ \\  \\ \\  \\::\\ \\     \\::\\ \\   \\:\\/___/\\\\:\\____/\\     /____\\:\\\\: \\ \\\\::\\ \\/__\\::\\__/\\\\ \\ \\   \n"
                "        \\_______\\/ \\__\\/\\__\\/   \\__\\/      \\__\\/    \\_____\\/ \\_____\\/     \\_____\\/ \\__\\/ \\::\\/\\________\\/ \\_\\/   \n"
                "\n\n----------------- ";

        SetConsoleTextAttribute(hConsole, 15);
        cout << "YOUR BOARD";
        SetConsoleTextAttribute(hConsole, 7);
        cout << " ------------------                        ------------------ ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "ENEMY BOARD";
        SetConsoleTextAttribute(hConsole, 7);
        cout << " ----------------\n|";

        SetConsoleTextAttribute(hConsole, 8);
        cout << "      A   B   C   D   E   F   G   H   I   J  ";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "|                        |";
        SetConsoleTextAttribute(hConsole, 8);
        cout << "      A   B   C   D   E   F   G   H   I   J  ";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "|\n|---------------------------------------------|                        |---------------------------------------------|\n";


        for (int row = 0; row<10; row++) {
            cout << "| ";
            SetConsoleTextAttribute(hConsole, 8);
            cout << row;
            SetConsoleTextAttribute(hConsole, 7);
            cout << " |";

            // player board
            for (int column = 0; column < 10; column++) {
                string ship = playerBoard[row][column];
                if(gamePhase == BUILDING && row == lastCursorPosition[0] && column == lastCursorPosition[1]) {
                    if(ship == "C" || ship == "B" || ship == "R" || ship == "S" || ship == "D") {
                        SetConsoleTextAttribute(hConsole, 112);
                        cout << "  " << ship << " ";
                    } else cout << "  " << square << " ";
                } else {
                    if(ship == "C") SetConsoleTextAttribute(hConsole, 16);
                    if(ship == "B") SetConsoleTextAttribute(hConsole, 48);
                    if(ship == "R") SetConsoleTextAttribute(hConsole, 63);
                    if(ship == "S") SetConsoleTextAttribute(hConsole, 144);
                    if(ship == "D") SetConsoleTextAttribute(hConsole, 160);
                    if(ship == "X") {
                        SetConsoleTextAttribute(hConsole, 12);
                        cout << "  X ";
                    } else if(ship == xchar) cout << "  " << xchar << " ";
                    else cout << "  " << ship << " ";
                }
                SetConsoleTextAttribute(hConsole, 7);
            }
            cout << " |                        | ";
            SetConsoleTextAttribute(hConsole, 8);
            cout << row;
            SetConsoleTextAttribute(hConsole, 7);
            cout << " |";

            // enemy board
            for (int column = 0; column < 10; column++) {
                if(gamePhase == SHOOTING) {
                    string ship = enemyBoard[row][column];
                    if(ship == "X") {
                        SetConsoleTextAttribute(hConsole, 12);
                        cout << "  X ";
                        SetConsoleTextAttribute(hConsole, 7);
                    } else if(ship == xchar) cout << "  " << xchar << " ";
                    else cout << "  " << dot << " ";

                } else cout << "  " << dot << " ";
            }
            cout << " |\n";
        }

        if(gamePhase == BUILDING) cout << "--------------- BUILDING PHASE ----------------                        -----------------------------------------------\n\n";
        else {
            cout << "----------------- ";
            SetConsoleTextAttribute(hConsole, 15);
            cout << playerShips;
            SetConsoleTextAttribute(hConsole, 7);
            cout << " SHIPS LEFT ----------------";
            cout << "                        ----------------- " ;
            SetConsoleTextAttribute(hConsole, 15);
            cout << enemyShips;
            SetConsoleTextAttribute(hConsole, 7);
            cout << " SHIPS LEFT ----------------\n\n";
        }
    };

    void printControls() {
        if(gamePhase == BUILDING) {
            cout << "Currently building ship: ";
            SetConsoleTextAttribute(hConsole, 15);
            cout << listOfAllShips[shipIndex];
            SetConsoleTextAttribute(hConsole, 10);

            cout << "       \n\nW = UP                     C - CHANGE TYPE OF A SHIP\n"
                    "S = DOWN                   F2 - SAVE BOARD - START GAME\n"
                    "A = LEFT                   ESC - END GAME\n"
                    "D = RIGHT\n";

            SetConsoleTextAttribute(hConsole, 7);
        }
    }

    void playerShooting() {
        char rowChar, columnChar;
        int row, column;
        while(whoIsShooting == PLAYER) {
            cout << "Row [0-9]:";
            SetConsoleTextAttribute(hConsole, 9);
            cin >> rowChar;
            SetConsoleTextAttribute(hConsole, 7);
            cout << "\n";
            if(isalpha(rowChar)) row = tolower(rowChar)-97;
            else row = rowChar-48;

            if(row >= 0 && row <= 9) {
                cout << "Column [A-J]:";
                SetConsoleTextAttribute(hConsole, 9);
                cin >> columnChar;
                SetConsoleTextAttribute(hConsole, 7);
                cout << "\n";
                if(isalpha(columnChar)) column = tolower(columnChar)-97;
                else column = columnChar-48;

                if(column >= 0 && column <= 9) {
                    string character = enemyBoard[row][column];
                    if(character != xchar && character != "X") {
                        if(character == "C" || character == "B" || character == "R" || character == "S" || character == "D") {
                            enemyBoard[row][column] = "X";
                            if(character == "C") {
                                enemyCARRIER--;
                                if(enemyCARRIER == 0) enemyShips -= 1;
                            }
                            else if(character == "B") {
                                enemyBATTLESHIP--;
                                if(enemyBATTLESHIP == 0) enemyShips -= 1;
                            }
                            else if(character == "R") {
                                enemyCRUISER--;
                                if(enemyCRUISER == 0) enemyShips -= 1;
                            }
                            else if(character == "S") {
                                enemySUBMARINE--;
                                if(enemySUBMARINE == 0) enemyShips -= 1;
                            }
                            else if(character == "D") {
                                enemyDESTROYER--;
                                if(enemyDESTROYER == 0) enemyShips -= 1;
                            }

                        } else enemyBoard[row][column] = xchar;
                        clearScreen();
                        updateBoard();
                        printControls();
                        whoIsShooting = ENEMY;
                        if(enemyShips != 0) return;
                        else if(enemyShips == 0) {
                            cout << "Player wins";
                            gamePhase = END;
                            whoIsShooting = NOONE;
                            return;
                        }
                    }
                }
            }
        }
    };

    void enemyShooting() {
        unsigned row = random(0, 9);
        unsigned column = random(0, 9);
        while(whoIsShooting == ENEMY) {
            string character = playerBoard[row][column];
            if(character != xchar && character != "X") {
                if(character == "C" || character == "B" || character == "R" || character == "S" || character == "D") {
                    playerBoard[row][column] = "X";
                    if(character == "C") {
                        CARRIER--;
                        if(CARRIER == 0) playerShips -= 1;
                    }
                    else if(character == "B") {
                        BATTLESHIP--;
                        if(BATTLESHIP == 0) playerShips -= 1;
                    }
                    else if(character == "R") {
                        CRUISER--;
                        if(CRUISER == 0) playerShips -= 1;
                    }
                    else if(character == "S") {
                        SUBMARINE--;
                        if(SUBMARINE == 0) playerShips -= 1;
                    }
                    else if(character == "D") {
                        DESTROYER--;
                        if(DESTROYER == 0) playerShips -= 1;
                    }
                } else playerBoard[row][column] = xchar;
                updateBoard();
                printControls();
                whoIsShooting = PLAYER;
                if(playerShips != 0) return;
                else if(enemyShips == 0) {
                    cout << "Enemy wins";
                    gamePhase = END;
                    whoIsShooting = NOONE;
                    return;
                }
            }
        }

    };

    void startShootingPhase() {
        while(true) {
            if(whoIsShooting == PLAYER) playerShooting();
            else if(whoIsShooting == ENEMY) enemyShooting();
            else if(whoIsShooting == NOONE) return;
        }
    }

    void removeCharsFromArray(const string& character) {
        for(auto & i : enemyBoard) {
            for(auto & j : i) {
                if(j == character) j = dot;
            }
        }
    };

    void generateEnemyShips() {
        int randomRow = random(0, 9);
        int randomColumn = random(0, 9);
        int randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
        int rowIncrement = 0;
        int columnIncrement = 0;
        int tries = 0;

        // CARRIER
        while(enemyCARRIER != 5) {
            string character = enemyBoard[randomRow+rowIncrement][randomColumn+columnIncrement];
            if((character == "B" || character == "R" || character == "S" || character == "D") || randomRow+rowIncrement < 0 || randomColumn+columnIncrement < 0 || randomRow+rowIncrement > 9 || randomColumn+columnIncrement > 9) {
                if(randomDirection == 0) rowIncrement = rowIncrement-1;
                else if(randomDirection == 1) columnIncrement = columnIncrement-1;

            } else if(character == dot) {
                enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement] = "C";
                enemyCARRIER++;
            }

            if(randomDirection == 0) {
                if(rowIncrement > -1) rowIncrement++;
                else rowIncrement--;

            } else if(randomDirection == 1) {
                if(columnIncrement > -1) columnIncrement++;
                else columnIncrement--;
            }

            if(tries == 10) {
                removeCharsFromArray("C");
                enemyCARRIER = 0;
                randomRow = random(0, 9);
                randomColumn = random(0, 9);
                randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
                rowIncrement = 0;
                columnIncrement = 0;
                tries = 0;
            } else tries++;
        }

        // BATTLESHIP
        randomRow = random(0, 9);
        randomColumn = random(0, 9);
        randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
        rowIncrement = 0;
        columnIncrement = 0;
        tries = 0;
        while(enemyBATTLESHIP != 4) {
            string character = enemyBoard[randomRow+rowIncrement][randomColumn+columnIncrement];
            if((character == "C" || character == "R" || character == "S" || character == "D") || randomRow+rowIncrement < 0 || randomColumn+columnIncrement < 0 || randomRow+rowIncrement > 9 || randomColumn+columnIncrement > 9) {
                if(randomDirection == 0) rowIncrement = rowIncrement-1;
                else if(randomDirection == 1) columnIncrement = columnIncrement-1;

            } else if(character == dot) {
                enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement] = "B";
                enemyBATTLESHIP++;
            }

            if(randomDirection == 0) {
                if(rowIncrement > -1) rowIncrement++;
                else rowIncrement--;

            } else if(randomDirection == 1) {
                if(columnIncrement > -1) columnIncrement++;
                else columnIncrement--;
            }

            if(tries == 10) {
                removeCharsFromArray("B");
                enemyBATTLESHIP = 0;
                randomRow = random(0, 9);
                randomColumn = random(0, 9);
                randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
                rowIncrement = 0;
                columnIncrement = 0;
                tries = 0;
            } else tries++;
        }

        // CRUISER
        randomRow = random(0, 9);
        randomColumn = random(0, 9);
        randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
        rowIncrement = 0;
        columnIncrement = 0;
        tries = 0;
        while(enemyCRUISER != 3) {
            string character = enemyBoard[randomRow+rowIncrement][randomColumn+columnIncrement];
            if((character == "B" || character == "C" || character == "S" || character == "D") || randomRow+rowIncrement < 0 || randomColumn+columnIncrement < 0 || randomRow+rowIncrement > 9 || randomColumn+columnIncrement > 9) {
                if(randomDirection == 0) rowIncrement = rowIncrement-1;
                else if(randomDirection == 1) columnIncrement = columnIncrement-1;

            } else if(character == dot) {
                enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement] = "R";
                enemyCRUISER++;
            }

            if(randomDirection == 0) {
                if(rowIncrement > -1) rowIncrement++;
                else rowIncrement--;

            } else if(randomDirection == 1) {
                if(columnIncrement > -1) columnIncrement++;
                else columnIncrement--;
            }

            if(tries == 10) {
                removeCharsFromArray("R");
                enemyCRUISER = 0;
                randomRow = random(0, 9);
                randomColumn = random(0, 9);
                randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
                rowIncrement = 0;
                columnIncrement = 0;
                tries = 0;
            } else tries++;
        }

        // SUBMARINE
        randomRow = random(0, 9);
        randomColumn = random(0, 9);
        randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
        rowIncrement = 0;
        columnIncrement = 0;
        tries = 0;
        while(enemySUBMARINE != 3) {
            string character = enemyBoard[randomRow+rowIncrement][randomColumn+columnIncrement];
            if((character == "B" || character == "R" || character == "C" || character == "D") || randomRow+rowIncrement < 0 || randomColumn+columnIncrement < 0 || randomRow+rowIncrement > 9 || randomColumn+columnIncrement > 9) {
                if(randomDirection == 0) rowIncrement = rowIncrement-1;
                else if(randomDirection == 1) columnIncrement = columnIncrement-1;

            } else if(character == dot) {
                enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement] = "S";
                enemySUBMARINE++;
            }

            if(randomDirection == 0) {
                if(rowIncrement > -1) rowIncrement++;
                else rowIncrement--;

            } else if(randomDirection == 1) {
                if(columnIncrement > -1) columnIncrement++;
                else columnIncrement--;
            }

            if(tries == 10) {
                removeCharsFromArray("S");
                enemySUBMARINE = 0;
                randomRow = random(0, 9);
                randomColumn = random(0, 9);
                randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
                rowIncrement = 0;
                columnIncrement = 0;
                tries = 0;
            } else tries++;
        }

        // DESTROYER
        randomRow = random(0, 9);
        randomColumn = random(0, 9);
        randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
        rowIncrement = 0;
        columnIncrement = 0;
        tries = 0;
        while(enemyDESTROYER != 2) {
            string character = enemyBoard[randomRow+rowIncrement][randomColumn+columnIncrement];
            if((character == "B" || character == "R" || character == "S" || character == "C") || randomRow+rowIncrement < 0 || randomColumn+columnIncrement < 0 || randomRow+rowIncrement > 9 || randomColumn+columnIncrement > 9) {
                if(randomDirection == 0) rowIncrement = rowIncrement-1;
                else if(randomDirection == 1) columnIncrement = columnIncrement-1;

            } else if(character == dot) {
                enemyBoard[randomRow + rowIncrement][randomColumn + columnIncrement] = "D";
                enemyDESTROYER++;
            }

            if(randomDirection == 0) {
                if(rowIncrement > -1) rowIncrement++;
                else rowIncrement--;

            } else if(randomDirection == 1) {
                if(columnIncrement > -1) columnIncrement++;
                else columnIncrement--;
            }

            if(tries == 10) {
                removeCharsFromArray("D");
                enemyDESTROYER = 0;
                randomRow = random(0, 9);
                randomColumn = random(0, 9);
                randomDirection = random(0, 1);   // 0 = vertical, 1 = horizontal
                rowIncrement = 0;
                columnIncrement = 0;
                tries = 0;
            } else tries++;
        }

    };

    void createBoard() {
        cout << "     _______   ________   _________  _________  __       ______       ______   ___   ___    ________  ______    \n"
                "    /_______/\\ /_______/\\ /________/\\/________/\\/_/\\     /_____/\\     /_____/\\ /__/\\ /__/\\  /_______/\\/_____/\\   \n"
                "    \\::: _  \\ \\\\::: _  \\ \\\\__.::.__\\/\\__.::.__\\/\\:\\ \\    \\::::_\\/_    \\::::_\\/_\\::\\ \\\\  \\ \\ \\__.::._\\/\\:::_ \\ \\  \n"
                "     \\::(_)  \\/_\\::(_)  \\ \\  \\::\\ \\     \\::\\ \\   \\:\\ \\    \\:\\/___/\\    \\:\\/___/\\\\::\\/_\\ .\\ \\   \\::\\ \\  \\:(_) \\ \\ \n"
                "      \\::  _  \\ \\\\:: __  \\ \\  \\::\\ \\     \\::\\ \\   \\:\\ \\____\\::___\\/_    \\_::._\\:\\\\:: ___::\\ \\  _\\::\\ \\__\\: ___\\/ \n"
                "       \\::(_)  \\ \\\\:.\\ \\  \\ \\  \\::\\ \\     \\::\\ \\   \\:\\/___/\\\\:\\____/\\     /____\\:\\\\: \\ \\\\::\\ \\/__\\::\\__/\\\\ \\ \\   \n"
                "        \\_______\\/ \\__\\/\\__\\/   \\__\\/      \\__\\/    \\_____\\/ \\_____\\/     \\_____\\/ \\__\\/ \\::\\/\\________\\/ \\_\\/   \n"
                "\n\n----------------- ";

        SetConsoleTextAttribute(hConsole, 15);
        cout << "YOUR BOARD";
        SetConsoleTextAttribute(hConsole, 7);
        cout << " ------------------                        ------------------ ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "ENEMY BOARD";
        SetConsoleTextAttribute(hConsole, 7);
        cout << " ----------------\n|";

        SetConsoleTextAttribute(hConsole, 8);
        cout << "      A   B   C   D   E   F   G   H   I   J  ";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "|                        |";
        SetConsoleTextAttribute(hConsole, 8);
        cout << "      A   B   C   D   E   F   G   H   I   J  ";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "|\n|---------------------------------------------|                        |---------------------------------------------|\n";

        for(unsigned row = 0; row<10; row++) {
            cout << "| ";
            SetConsoleTextAttribute(hConsole, 8);
            cout << row;
            SetConsoleTextAttribute(hConsole, 7);
            cout << " |";

            // player board
            for(unsigned column = 0; column < 10; column++) {
                playerBoard[row][column] = dot;
                if(row == lastCursorPosition[0] && column == lastCursorPosition[1]) {
                    cout << "  " << square << " ";
                } else {
                    cout << "  " << dot << " ";
                }
            }
            cout << " |                        | ";
            SetConsoleTextAttribute(hConsole, 8);
            cout << row;
            SetConsoleTextAttribute(hConsole, 7);
            cout << " |";

            // enemy board
            for (unsigned column = 0; column < 10; column++) {
                enemyBoard[row][column] = dot;
                cout << "  " << dot << " ";
            }
            cout << " |\n";
        }

        cout << "--------------- BUILDING PHASE ----------------                        --------------- BUILDING PHASE ----------------\n\n";
        generateEnemyShips();
        printControls();

        // key logs
        while(true) {
            if(GetAsyncKeyState(0x41)) {                        // A - LEFT KEY
                if(lastCursorPosition[1] != 0) {
                    lastCursorPosition[1] -= 1;
                    updateBoard();
                    printControls();
                }

            } else if(GetAsyncKeyState(0x44)) {                // D - RIGHT KEY
                if(lastCursorPosition[1] != 9) {
                    lastCursorPosition[1] += 1;
                    updateBoard();
                    printControls();
                }

            } else if(GetAsyncKeyState(0x57)) {                // W - UP KEY
                if(lastCursorPosition[0] != 0) {
                    lastCursorPosition[0] -= 1;
                    updateBoard();
                    printControls();
                }

            } else if(GetAsyncKeyState(0x53)) {                // S - DOWN KEY
                if(lastCursorPosition[0] != 9) {
                    lastCursorPosition[0] += 1;
                    updateBoard();
                    printControls();
                }

            } else if(GetAsyncKeyState(0x0D)) {                // ENTER KEY
                string character = playerBoard[lastCursorPosition[0]][lastCursorPosition[1]];
                if(shipIndex == 0) {
                    if(character != "C" && canPlaceShip("C")) {
                        if(CARRIER == 5) shipIndex++;
                        else {
                            if(character == "B") BATTLESHIP--;
                            else if(character == "R") CRUISER--;
                            else if(character == "S") SUBMARINE--;
                            else if(character == "D") DESTROYER--;
                            playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = "C";
                            updateBoard();
                            printControls();
                            CARRIER++;
                            if(CARRIER == 5) shipIndex++;
                        }
                    }

                } else if(shipIndex == 1) {
                    if(character != "B" && canPlaceShip("B")) {
                        if(BATTLESHIP == 4) shipIndex++;
                        else {
                            if(character == "C") CARRIER--;
                            else if(character == "R") CRUISER--;
                            else if(character == "S") SUBMARINE--;
                            else if(character == "D") DESTROYER--;
                            playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = "B";
                            updateBoard();
                            printControls();
                            BATTLESHIP++;
                            if(BATTLESHIP == 4) shipIndex++;
                        }
                    }

                } else if(shipIndex == 2) {
                    if(character != "R" && canPlaceShip("R")) {
                        if(CRUISER == 3) shipIndex++;
                        else {
                            if(character == "C") CARRIER--;
                            else if(character == "B") BATTLESHIP--;
                            else if(character == "S") SUBMARINE--;
                            else if(character == "D") DESTROYER--;
                            playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = "R";
                            updateBoard();
                            printControls();
                            CRUISER++;
                            if(CRUISER == 3) shipIndex++;
                        }
                    }

                } else if(shipIndex == 3) {
                    if(character != "S" && canPlaceShip("S")) {
                        if(SUBMARINE == 3) shipIndex++;
                        else {
                            if(character == "C") CARRIER--;
                            else if(character == "B") BATTLESHIP--;
                            else if(character == "R") CRUISER--;
                            else if(character == "D") DESTROYER--;
                            playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = "S";
                            updateBoard();
                            printControls();
                            SUBMARINE++;
                            if(SUBMARINE == 3) shipIndex++;
                        }
                    }

                } else if(shipIndex == 4) {
                    if(character != "D" && canPlaceShip("D")) {
                        if(DESTROYER == 2) shipIndex = 0;
                        else {
                            if(character == "C") CARRIER--;
                            else if(character == "B") BATTLESHIP--;
                            else if(character == "R") CRUISER--;
                            else if(character == "S") SUBMARINE--;
                            playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = "D";
                            updateBoard();
                            printControls();
                            DESTROYER++;
                            if(DESTROYER == 2) shipIndex = 0;
                        }
                    }

                }

            } else if(GetAsyncKeyState(VK_BACK)) {              // BACKSPACE KEY
                string character = playerBoard[lastCursorPosition[0]][lastCursorPosition[1]];
                if(canDeleteLocation(character)) {
                    if(character == "C") {
                        playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = dot;
                        shipIndex = 0;
                        CARRIER--;
                    } else if(character == "B") {
                        playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = dot;
                        shipIndex = 1;
                        BATTLESHIP--;
                    } else if(character == "R") {
                        playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = dot;
                        shipIndex = 2;
                        CRUISER--;
                    } else if(character == "S") {
                        playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = dot;
                        shipIndex = 3;
                        SUBMARINE--;
                    } else if(character == "D") {
                        playerBoard[lastCursorPosition[0]][lastCursorPosition[1]] = dot;
                        shipIndex = 4;
                        DESTROYER--;
                    }
                    updateBoard();
                    printControls();
                }

            } else if(GetAsyncKeyState(0x43)) {              // C KEY
                shipIndex++;
                if(shipIndex > 4) shipIndex = 0;
                updateBoard();
                printControls();

            } else if(GetAsyncKeyState(VK_F2)) {                // F2 KEY
                if(CARRIER == 5 && BATTLESHIP == 4 && CRUISER == 3 && SUBMARINE == 3 && DESTROYER == 2) {
                    gamePhase = SHOOTING;
                    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                    clearScreen();
                    updateBoard();
                    printControls();
                    startShootingPhase();
                    return;
                }
            } else if(GetAsyncKeyState(VK_ESCAPE)) return;
            Sleep(100);
        }
    }
};

int main() {
    BattleShipMinigame game;
    game.start();

    return 0;
}
