#include <iostream>
#include "engine.h"

Engine::Engine() 
    : thread_lan_(&Engine::LanGame, this)//, thread_draw_(&Engine::EngineDraw, this)
{
    std::this_thread::get_id(); // Get id thread of LanGame
    this->CreateResolutionWindowMode();
}

void Engine::CreateResolutionWindowMode() {
    sf::Vector2f resolution;
    resolution.x = SCREEN_RESOLUTION_X;
    resolution.y = SCREEN_RESOLUTION_Y;

    Main_window_.create(sf::VideoMode(int(resolution.x), int(resolution.y)), "TANKS", sf::Style::Default);
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

void Engine::Font() { Main_font_.loadFromFile("Data/Font/Font.ttf"); }

Engine::~Engine() { 
    thread_lan_.join();
    /*
    for (std::vector<sf::TcpSocket*>::iterator it = list_clients_.begin(); 
        it != list_clients_.end(); it++)
        delete* it;
    */
}