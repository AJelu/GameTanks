#include <iostream>
#include "run_game.h"

int main() {
    std::cout << "Console message: Game Run!" << std::endl; //this is for the test!
    RunGame();
    return 0;
}

void RunGame() {
    std::cout << "Address local: " << sf::IpAddress::getLocalAddress()
        << "; Address public: " << sf::IpAddress::getPublicAddress() << std::endl;

    srand((unsigned int)time(NULL));

    Engine engine;

    GameLevel Game_level;
    engine.ChangeLevel(&Game_level);

    std::string connect_type;

    int state = 0;
    while (true) {
        while (!engine.GetStatusServer()) {
            std::cout << "Select type to connect: (s): server; (c): client; "
                << "(q) - quit game; ";
            std::cin >> connect_type;
            system("cls");

            if (connect_type == "s") { engine.SetStatusServer("SERVER"); break; }
            else if (connect_type == "c") { engine.SetStatusServer("CLIENT"); break; }
            else if (connect_type == "q") exit(0);
            else std::cout << "The wrong type is selected!" << std::endl;
        }

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