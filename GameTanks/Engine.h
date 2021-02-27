#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "RunGame.h"
#include "Levels.h"

#include "TestUnitController.h" /* TESTING MODULE! */

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
	BaseLevel *Draw_level;

	bool im_server;

	void GameTimer(float& timer); // create main game timer
	void GameSpeed(float& timer); // regulates the speed of the game
	void ForcedResetGameTimer(float& timer); // forced timer reset (may be needed if the reset does not work)

	void CreateResolutionWindowMode();

	void EngineInpute();
	void EngineUpdate(float& timer);
	void EngineDraw();

	bool LanGame();

	bool SendMessageToClient();
	bool RecvMessageFromServer();

	void Font();

	Unit TestUnit{ FloatRect(300, 300, 100, 100) }; /* TESTING UNIT! */

public:
	Engine();

	int Start();
	void Stop();

	void ChangeLevel(BaseLevel level);
};
