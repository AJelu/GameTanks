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

    Engine* engine = new Engine();;
    sf::Packet Level_result;

    BaseLevel* level;
    level = new MenuLevel();
    engine->ChangeLevel(level);

    std::string connect_type;

    int state = 0;
    while (true) {
        if (level->ExitLevel(Level_result)) {
            int type_load_level = BaseLevel::Level_type::EXIT;
            std::string ip_connect = "";
            BaseLevel* l = nullptr;

            Level_result >> type_load_level;
            if (type_load_level == BaseLevel::Level_type::EXIT) {
                break;
            }
            else if (type_load_level == BaseLevel::Level_type::GAME_LEVEL) {
                Level_result >> ip_connect;
                if (ip_connect == "") {
                    l = new GameLevel();
                    engine->ChangeLevel(l);
                    engine->StartServer();
                    delete level;
                    level = l;
                }
                else {
                    engine->PauseClientRecv(true);
                    engine->ConnectLanToIp(ip_connect);
                    while (engine->GetRecvIdFromServer() == 0 && engine->ServerIsWork()) {
                        //white id client object
                        std::cout << "";
                    }
                    if (engine->GetRecvIdFromServer() != 0) {
                        l = new GameLevel(engine->GetRecvIdFromServer());
                        engine->ChangeLevel(l);
                        delete level;
                        level = l;
                    }
                    engine->PauseClientRecv(false);
                }
            }
            else if (type_load_level == BaseLevel::Level_type::MENU_LEVEL) {
                l = new MenuLevel();
                engine->StopServer();
                engine->ChangeLevel(l);
                delete level;
                level = l;
            }
        }
        Level_result.clear(); 

        state = engine->Start();
        if (state == 0) {
            //logic game instance
        }
        else if (state == 1) {
            std::cout << "Console message: Exit game!" << std::endl; //this is for the test!
            engine->Stop();
            break;
        }
        else if (state == 2) {
            engine->Stop();
            std::cout << "Console message: Game Restart!" << std::endl; //this is for the test!
            RunGame();
        }
    }
    std::cout << "Console message: Game Quit!" << std::endl; //this is for the test!
    delete engine;
    delete level;
}