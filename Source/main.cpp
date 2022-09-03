#include "main.h"


int main()
{
    // Get the console handle
    HWND console = GetConsoleWindow();

    // Set window size
    // MoveWindow(window_handle, x, y, width, height, redraw_window);
    MoveWindow(console, 100, 100, 992, 548, TRUE);

    // Start game
    BattleshipMinigame game;
    game.start();

    std::string t;
    std::cin >> t;

    return 0;
}
