#include <iostream>
#include "run_game.h"
#include "objects.h"

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
                    int err_int = 0;
                    while (engine->GetRecvIdFromServer() == 0 && engine->ServerIsWork()) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                        err_int++;
                        if (err_int > 1000) break;
                    }
                    if (engine->GetRecvIdFromServer() != 0) {
                        l = new GameLevel(engine->GetRecvIdFromServer());
                        engine->ChangeLevel(l);
                        delete level;
                        level = l;
                    }
                    engine->PauseClientRecv(false);
                    if (err_int > 1000) engine->StopServer();
                }
            }
            else if (type_load_level == BaseLevel::Level_type::MENU_LEVEL) {
                engine->StopServer();
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                l = new MenuLevel();
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

    VisibleObject::DestroyCreatedStaticVectors();
    AudioObject::DestroyCreatedStaticVectors();
}