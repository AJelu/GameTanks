#include <iostream>
#include "engine.h"

Engine::Engine()
    : pause_client_recv_(false), 
    status_server_(StatusServer::NOT_DETERMINED)/*, 
    thread_lan_(&Engine::LanGame, this)*/ {

    //std::this_thread::get_id(); // Get id thread of LanGame
    this->CreateResolutionWindowMode();
    thread_lan_ = nullptr;
}

void Engine::CreateResolutionWindowMode() {

    //FULL SCREEN GAME
    sf::Vector2f resolution;
    resolution.x = SCREEN_RESOLUTION_X;
    resolution.y = SCREEN_RESOLUTION_Y;

    Main_window_.create(sf::VideoMode(int(resolution.x), int(resolution.y)), "TANKS", sf::Style::Fullscreen);
    Main_window_.setFramerateLimit(60);
}

int Engine::Start() {
    sf::Event game;
    
    if (Main_window_.isOpen()) { //launch all game events during game time iteration
        /*while (Main_window_.pollEvent(game)) {
            if (game.type == sf::Event::Closed) Main_window_.close(); //close the window
            if (game.type == sf::Event::KeyReleased && game.key.code == sf::Keyboard::Q) return 1;
            if (game.type == sf::Event::KeyReleased && game.key.code == sf::Keyboard::R) return 2;
        }*/ //touch 'Q' to exit and touch 'R' to restart

        float game_time;
        this->GameTimer(game_time);
        this->GameSpeed(game_time);
        //this->ForcedResetGameTimer(game_time);

        this->EngineInpute();
        this->EngineUpdate(game_time);
        this->EngineDraw();

        if (status_server_ == StatusServer::SERVER)
            this->ServerMailingMessageToClients();

        return 0;
    }
    return 1;
}

void Engine::Stop() { Main_window_.close(); }

void Engine::ChangeLevel(BaseLevel* level) {
    if (level != nullptr) Point_level_ = level;
}

void Engine::GameTimer(float& timer) {
    timer = static_cast<float>(Game_clock_.getElapsedTime().asMicroseconds());
    Game_clock_.restart(); //update the game logic
}

void Engine::GameSpeed(float& timer) { timer = timer / GAME_SPEED_CONTROLLER; }

void Engine::ForcedResetGameTimer(float& timer) { if (timer > GAME_TIMER_LIMIT) timer = 0; }

void Engine::StartServer() {
    this->StopServer();
    lan_thread_work_ = true;
    status_server_ = StatusServer::SERVER;
    thread_lan_ = new std::thread(&Engine::LanGame, this);
}

void Engine::StopServer() {
    status_server_ = StatusServer::NOT_DETERMINED;
    lan_thread_work_ = false;
    tcp_selector_.clear();
    server.close();
    if (thread_lan_ != nullptr) {
        thread_lan_->join();
        delete thread_lan_;
        thread_lan_ = nullptr;
    }
    this->CleaningClients();
    list_clients_.clear();
    tcp_socket_.disconnect();
}

void Engine::ConnectLanToIp(std::string const& ip_to_connect) {
    ip_client_connect_ = ip_to_connect;
    client_id_object_ = 0;
    this->StopServer();
    lan_thread_work_ = true;
    status_server_ = StatusServer::CLIENT;
    thread_lan_ = new std::thread(&Engine::LanGame, this);
}

int Engine::GetRecvIdFromServer() {
    return client_id_object_;
}

void Engine::PauseClientRecv(bool const& pause_client_recv) {
    pause_client_recv_ = pause_client_recv;
}

bool Engine::ServerIsWork() {
    return status_server_ != StatusServer::NOT_DETERMINED;
}

Engine::~Engine() {
    this->StopServer();
}