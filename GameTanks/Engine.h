#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
#include "run_game.h"
#include "levels.h"
#include "objects.h"

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
	Clock Game_clock;
	RenderWindow Main_window; // this object is responsible for all render
	BaseLevel Point_level;
	Font Main_font;

	bool im_server;

	void GameTimer(float& timer); // create main game timer
	void GameSpeed(float& timer); // regulates the speed of the game
	void ForcedResetGameTimer(float& timer); // forced timer reset (may be needed if the reset does not work)

	void CreateResolutionWindowMode();

	void EngineInpute();
	void EngineUpdate(float& timer);
	void EngineDraw(float& timer);

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
