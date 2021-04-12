#include <iostream>
#include "run_game.h"
#include "objects.h"

int main() {
    RunGame();
    return 0;
}

void RunGame() {
    /*std::cout << "Address local: " << sf::IpAddress::getLocalAddress()
        << "; Address public: " << sf::IpAddress::getPublicAddress() << std::endl;*/
    GameObject::DisplayCollision(false); //showing collisions
    srand((unsigned int)time(NULL));

    Engine* engine = new Engine();
    sf::Packet Level_result;

    BaseLevel* level;
    level = new MenuLevel();
    engine->ChangeLevel(level);

    while (true) {
        if (level->CheckExitLevel(Level_result)) {
            int type_load_level = int(BaseLevel::Level_type::EXIT);
            std::string ip_connect = "";
            BaseLevel* Temp_level = nullptr;

            Level_result >> type_load_level;
            if (type_load_level == int(BaseLevel::Level_type::EXIT)) {
                break;
            }
            else if (type_load_level == int(BaseLevel::Level_type::GAME_LEVEL)) {
                Level_result >> ip_connect;

                //Level load frame:
                BaseLevel* Load_level; 
                if (ip_connect == "")   Load_level = new LoadLevel("Loading...");
                else                    Load_level = new LoadLevel("Connecting...");
                engine->ChangeLevel(Load_level);
                engine->Processing();
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                engine->Processing();
                engine->ChangeLevel(level);
                delete Load_level;
                Load_level = nullptr;

                //Level Server
                if (ip_connect == "") {
                    Temp_level = new GameLevel();
                    engine->ChangeLevel(Temp_level);
                    engine->StartLanServer();
                    delete level;
                    level = Temp_level;
                }

                //Level Client
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
                        Temp_level = new GameLevel(engine->GetRecvIdFromServer());
                        engine->ChangeLevel(Temp_level);
                        delete level;
                        level = Temp_level;
                    } 
                    else engine->StopLanServer();
                    engine->PauseClientRecv(false);
                }
            }
            else if (type_load_level == int(BaseLevel::Level_type::MENU_LEVEL)) {
                engine->StopLanServer();
                Temp_level = new MenuLevel();
                engine->ChangeLevel(Temp_level);
                delete level;
                level = Temp_level;
            }
        }
        Level_result.clear(); 
        engine->Processing();
    }
    BaseLevel* Load_level = new LoadLevel("Exit...");
    engine->ChangeLevel(Load_level);
    engine->Processing();
    delete Load_level;
    Load_level = nullptr;
    delete engine;
    delete level;

    VisibleObject::DestroyCreatedStaticVectors();
    AudioObject::DestroyCreatedStaticVectors();
}