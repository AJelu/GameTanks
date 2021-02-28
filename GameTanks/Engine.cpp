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

    mainWindow.create(VideoMode(int(resolution.x), int(resolution.y)), "TANKS", Style::Default);
    mainWindow.setFramerateLimit(60);
}

int Engine::Start()
{
    Event game; 
    if (mainWindow.isOpen()) { //launch all game events during game time iteration
        while (mainWindow.pollEvent(game)) {
            if (game.type == Event::Closed) mainWindow.close(); //close the window
            if (game.type == Event::KeyReleased && game.key.code == Keyboard::Q) return 1;
            if (game.type == Event::KeyReleased && game.key.code == Keyboard::R) return 2;
        } //touch 'Q' to exit and touch 'R' to restart

        float game_time;
        GameTimer(game_time);
        GameSpeed(game_time);
        //ForcedResetGameTimer(game_time);
        /*
        EngineInpute();
        EngineUpdate(game_time);
        LanGame();
        EngineDraw();
        */
        mainWindow.clear(Color::Black);

        TestUnit.UnitUpdateWithDrawWithInput(mainWindow, game_time); /*test*/

        mainWindow.display(); //end the current frame
        return 0;
    }
    return 1;
}

void Engine::Stop() { mainWindow.close(); }

void Engine::ChangeLevel(BaseLevel level)
{
}

void Engine::GameTimer(float& timer)
{
    timer = static_cast<float>(GameClock.getElapsedTime().asMicroseconds());
    GameClock.restart(); //update the game logic
}

void Engine::GameSpeed(float& timer) { timer = timer / GAME_SPEED_CONTROLLER; }

void Engine::ForcedResetGameTimer(float& timer) { if (timer > GAME_TIMER_LIMIT) timer = 0; }

void Engine::Font() {}