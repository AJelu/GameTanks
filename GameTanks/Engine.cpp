#include <iostream>
#include "engine.h"

Engine::Engine()
        : pause_client_recv_(false), 
        Status_server_(StatusServer::NOT_DETERMINED) {
    this->CreateResolutionWindowMode();
    Thread_lan_ = nullptr;
}

void Engine::CreateResolutionWindowMode() {
    sf::Vector2f resolution;
    resolution.x = SCREEN_RESOLUTION_X;
    resolution.y = SCREEN_RESOLUTION_Y;
    Main_window_.create(sf::VideoMode(int(resolution.x), int(resolution.y)), 
        "TANKS", sf::Style::Fullscreen);
    Main_window_.setFramerateLimit(60);
}

int Engine::Processing() {
    if (Main_window_.isOpen()) { 
        float game_time;
        this->GameTimer(game_time);
        this->GameSpeed(game_time);
        this->EngineInpute();
        this->EngineUpdate(game_time);
        this->EngineDraw();
        if (Status_server_ == StatusServer::SERVER) 
            this->ServerMailingMessageToClients();
        return 0;
    }
    return 1;
}

void Engine::ChangeLevel(BaseLevel* level) { 
    if (level != nullptr) Point_level_ = level;
}

void Engine::GameTimer(float& timer) {
    timer = static_cast<float>(Game_clock_.getElapsedTime().asMicroseconds());
    Game_clock_.restart(); //update the game logic
}

void Engine::GameSpeed(float& timer) { timer = timer / GAME_SPEED_CONTROLLER; }

void Engine::StartLanServer() {
    this->StopLanServer();
    lan_thread_work_ = true;
    Status_server_ = StatusServer::SERVER;
    Thread_lan_ = new std::thread(&Engine::LanGame, this);
}

void Engine::StopLanServer() {
    Status_server_ = StatusServer::NOT_DETERMINED;
    lan_thread_work_ = false;
    Tcp_selector_.clear();
    Server_.close();
    if (Thread_lan_ != nullptr) {
        Thread_lan_->join();
        delete Thread_lan_;
        Thread_lan_ = nullptr;
    }
    this->CleaningClients();
    List_clients_.clear();
    Tcp_socket_.disconnect();
}

void Engine::ConnectLanToIp(std::string const& ip_to_connect) {
    Ip_client_connect_ = ip_to_connect;
    client_id_object_ = 0;
    this->StopLanServer();
    lan_thread_work_ = true;
    Status_server_ = StatusServer::CLIENT;
    Thread_lan_ = new std::thread(&Engine::LanGame, this);
}

int Engine::GetRecvIdFromServer() { return client_id_object_; }

void Engine::PauseClientRecv(bool const& pause_client_recv) {
    pause_client_recv_ = pause_client_recv;
}

bool Engine::ServerIsWork() {
    return Status_server_ != StatusServer::NOT_DETERMINED;
}

Engine::~Engine() { this->StopLanServer(); }