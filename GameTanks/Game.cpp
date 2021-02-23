#include <iostream>
#include "RunGame.h"

int main()
{
    std::cout << "Console message: Game Run!" << endl; //this is for the test!
    RunGame();
    return 0;
}

void RunGame()
{
    Engine engine;
    if (engine.Start()) {
        engine.Stop();
        std::cout << "Console message: Game Restart!" << endl; //this is for the test!
        RunGame();
    }
    std::cout << "Console message: Game Quit!" << endl; //this is for the test!
}