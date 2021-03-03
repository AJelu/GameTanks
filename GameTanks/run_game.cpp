#include <iostream>
#include "run_game.h"

int main()
{
    std::cout << "Console message: Game Run!" << endl; //this is for the test!
    RunGame();
    return 0;
}

void RunGame()
{
    Engine engine;
    int state = 0;
    while (true) {
        state = engine.Start();
        if (state == 0) {
            //logic game instance
        }
        else if (state == 1) {
            engine.Stop();
            break;
        }
        else if (state == 2) {
            engine.Stop();
            std::cout << "Console message: Game Restart!" << endl; //this is for the test!
            RunGame();
        }  
    }
    std::cout << "Console message: Game Quit!" << endl; //this is for the test!
}