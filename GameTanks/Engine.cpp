#include "Engine.h"

Engine::Engine() 
{
    CreateResolutionWindowMode();
}

void Engine::CreateResolutionWindowMode()
{
    Vector2f resolution;
    resolution.x = 1024;
    resolution.y = 768;

    mainWindow.create(VideoMode(resolution.x, resolution.y), "TANKS", Style::Default);
    mainWindow.setFramerateLimit(60);
}

bool Engine::Start()
{
    Event game; 
    while (mainWindow.isOpen()) { //launch all game events during game time iteration
        while (mainWindow.pollEvent(game)) {
            if (game.type == Event::Closed) mainWindow.close(); //close the window
            if (game.type == Event::KeyReleased && game.key.code == Keyboard::Q) return false;
            if (game.type == Event::KeyReleased && game.key.code == Keyboard::R) return true;
        } //touch 'Q' to exit and touch 'R' to restart

        float game_time;
        GameTimer(game_time);
        GameSpeed(game_time);
        //ForcedResetGameTimer(game_time);

        /*
        Audio();
        LanGame();
        EngineInpute();
        EngineUpdate();
        */

        mainWindow.clear(sf::Color::Black); //temporarily paint the main window with color
        mainWindow.display(); //end the current frame
    }
    return false;
}

void Engine::Stop() { mainWindow.close(); }

void Engine::GameTimer(float& timer)
{
    float game_time = static_cast<float>(GameClock.getElapsedTime().asMicroseconds());
    GameClock.restart(); //update the game logic
}

void Engine::GameSpeed(float& timer) { timer = timer / GAME_SPEED_CONTROLLER; }

void Engine::ForcedResetGameTimer(float& timer) { if (timer > GAME_TIMER_LIMIT) timer = 0; }