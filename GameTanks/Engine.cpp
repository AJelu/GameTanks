#include <iostream>
#include "engine.h"

Engine::Engine() 
{
    CreateResolutionWindowMode();
}

void Engine::CreateResolutionWindowMode()
{
    Vector2f resolution;
    resolution.x = 1024;
    resolution.y = 768;

    Main_window.create(VideoMode(int(resolution.x), int(resolution.y)), "TANKS", Style::Default);
    Main_window.setFramerateLimit(60);
}

int Engine::Start()
{
    Event game; 
    if (Main_window.isOpen()) { //launch all game events during game time iteration
        while (Main_window.pollEvent(game)) {
            if (game.type == Event::Closed) Main_window.close(); //close the window
            if (game.type == Event::KeyReleased && game.key.code == Keyboard::Q) return 1;
            if (game.type == Event::KeyReleased && game.key.code == Keyboard::R) return 2;
        } //touch 'Q' to exit and touch 'R' to restart

        float game_time;
        GameTimer(game_time);
        GameSpeed(game_time);
        //ForcedResetGameTimer(game_time);

        EngineInpute();
        EngineUpdate(game_time);
        LanGame();
        EngineDraw(game_time);

        return 0;
    }
    return 1;
}

void Engine::Stop() { Main_window.close(); }

void Engine::ChangeLevel(BaseLevel level)
{
}

void Engine::GameTimer(float& timer)
{
    timer = static_cast<float>(Game_clock.getElapsedTime().asMicroseconds());
    Game_clock.restart(); //update the game logic
}

void Engine::GameSpeed(float& timer) { timer = timer / GAME_SPEED_CONTROLLER; }

void Engine::ForcedResetGameTimer(float& timer) { if (timer > GAME_TIMER_LIMIT) timer = 0; }

void Engine::Font() { Main_font.loadFromFile("Data/Font/Font.ttf"); }