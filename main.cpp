#include <iostream>

using namespace std;

class BattleShipMinigame {
    int playerBoard[10][10];
    int enemyBoard[10][10];
    int rows = 10, columns = 10;

    public:
    void start() {
        createBoard();
    };
    private:
    void createBoard() {
        cout << "  _______   ________   _________  _________  __       ______       ______   ___   ___    ________  ______    \n"
                "/_______/\\ /_______/\\ /________/\\/________/\\/_/\\     /_____/\\     /_____/\\ /__/\\ /__/\\  /_______/\\/_____/\\   \n"
                "\\::: _  \\ \\\\::: _  \\ \\\\__.::.__\\/\\__.::.__\\/\\:\\ \\    \\::::_\\/_    \\::::_\\/_\\::\\ \\\\  \\ \\ \\__.::._\\/\\:::_ \\ \\  \n"
                " \\::(_)  \\/_\\::(_)  \\ \\  \\::\\ \\     \\::\\ \\   \\:\\ \\    \\:\\/___/\\    \\:\\/___/\\\\::\\/_\\ .\\ \\   \\::\\ \\  \\:(_) \\ \\ \n"
                "  \\::  _  \\ \\\\:: __  \\ \\  \\::\\ \\     \\::\\ \\   \\:\\ \\____\\::___\\/_    \\_::._\\:\\\\:: ___::\\ \\  _\\::\\ \\__\\: ___\\/ \n"
                "   \\::(_)  \\ \\\\:.\\ \\  \\ \\  \\::\\ \\     \\::\\ \\   \\:\\/___/\\\\:\\____/\\     /____\\:\\\\: \\ \\\\::\\ \\/__\\::\\__/\\\\ \\ \\   \n"
                "    \\_______\\/ \\__\\/\\__\\/   \\__\\/      \\__\\/    \\_____\\/ \\_____\\/     \\_____\\/ \\__\\/ \\::\\/\\________\\/ \\_\\/   \n"
                "                                                                                                             \n\n";

        cout << "----------------- YOUR BOARD ------------------                        ------------------ ENEMY BOARD ----------------\n"
                "|      A   B   C   D   E   F   G   H   I   J  |                        |      A   B   C   D   E   F   G   H   I   J  |\n"
                "|---------------------------------------------|                        |---------------------------------------------|\n";


        for(int row = 0;row < rows;row++) {
            cout << "| " << row << " |";

            // player board
            for(int column = 0;column < columns;column++) {
                cout << "  " << (char)250 << " ";
            }
            cout << " |                        | " << row << " |";

            // enemy board
            for(int column = 0;column < columns;column++) {
                cout << "  " << (char)250 << " ";
            }
            cout << " |" << endl;
        }

        cout << "----------------- 10 BOATS LEFT ----------------                        ----------------- X BOATS LEFT ----------------\n"
        "\nEnter coordinates of \n"
        "\n";

    // 1 loď o délce 5 (CARRIER)
    // 1 loď o délce 4 (BATTLESHIP)
    // 2 lodě o délce 3 (SUBMARINE & CRUISER)
    // 2 lodě o délce 2 (DESTROYER)
    // https://www.hasbro.com/common/instruct/Battleship.PDF

            cout <<endl<< (char)176 << " 176" << endl;
            cout << (char)177 << " 177"<< endl;
            cout << (char)178 << " 178"<< endl;
            cout << (char)240 << " 240"<< endl;
            cout << (char)219 << " 219"<< endl;
            cout << (char)254u << " 254u"<< endl;
    };
};

int main() {
    BattleShipMinigame game;
    game.start();

    return 0;
}
