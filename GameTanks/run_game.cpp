#include <iostream>
#include "run_game.h"

int main() {
    std::cout << "Console message: Game Run!" << std::endl; //this is for the test!
    RunGame();
    return 0;
}

void RunGame() {
    srand((unsigned int)time(NULL));

    Engine engine;

    GameLevel Game_level;
    engine.ChangeLevel(&Game_level);

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
            std::cout << "Console message: Game Restart!" << std::endl; //this is for the test!
            RunGame();
        }  
    }
    std::cout << "Console message: Game Quit!" << std::endl; //this is for the test!
}