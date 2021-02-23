#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "RunGame.h"
#include "Levels.h"

/*
	Engine includes the following files :
		Engine.cpp
		LanGame.cpp
		Audio.cpp
		EngineUpdate.cpp
		EngineInput.cpp
*/

using namespace sf;

class Engine {
private:
	Clock GameClock;
	RenderWindow mainWindow; // this object is responsible for all render

	void GameTimer(float& timer); // create main game timer
	void GameSpeed(float& timer); // regulates the speed of the game
	void ForcedResetGameTimer(float& timer); // forced timer reset (may be needed if the reset does not work)

	void CreateResolutionWindowMode();
	void EngineInpute();
	void EngineUpdate();

	bool LanGame();
	void Audio();

public:
	Engine();

	bool Start();
	void Stop();
};
