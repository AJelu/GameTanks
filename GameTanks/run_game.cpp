#include <iostream>
#include <chrono>
#include <thread>
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

    /* Testing thread to draw */
    //std::thread thread_draw_(&Engine::EngineDraw, &engine);
    //std::this_thread::get_id(); 
    
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

    //std::this_thread::sleep_for(std::chrono::milliseconds(16));
    //thread_draw_.join();

    std::cout << "Console message: Game Quit!" << std::endl; //this is for the test!
}