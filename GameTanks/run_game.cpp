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
    GameObject::DisplayCollision(true); //showing collisions
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
                //show load frame
                BaseLevel* Load_level; 
                if (ip_connect == "")   Load_level = new LoadLevel("Loading...");
                else                    Load_level = new LoadLevel("Connecting...");
                engine->ChangeLevel(Load_level);
                engine->Start();
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                engine->Start();
                engine->ChangeLevel(level);
                delete Load_level;
                Load_level = nullptr;
                /*----------------*/
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
                        if (err_int > 10000) break;
                    }
                    if (engine->GetRecvIdFromServer() != 0) {
                        l = new GameLevel(engine->GetRecvIdFromServer());
                        engine->ChangeLevel(l);
                        delete level;
                        level = l;
                    } else engine->StopServer();
                    engine->PauseClientRecv(false);
                }
            }
            else if (type_load_level == BaseLevel::Level_type::MENU_LEVEL) {
                engine->StopServer();
                l = new MenuLevel();
                engine->ChangeLevel(l);
                delete level;
                level = l;
            }
        }
        Level_result.clear(); 

        /*state = */engine->Start();
        /*if (state == 0) {
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
        }*/
    }
    BaseLevel* Load_level = new LoadLevel("Exit...");
    engine->ChangeLevel(Load_level);
    engine->Start();
    delete Load_level;
    Load_level = nullptr;
    std::cout << "Console message: Game Quit!" << std::endl; //this is for the test!
    delete engine;
    delete level;

    VisibleObject::DestroyCreatedStaticVectors();
    AudioObject::DestroyCreatedStaticVectors();
}