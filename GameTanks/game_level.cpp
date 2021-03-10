#include "Levels.h"

GameLevel::GameLevel() : BaseLevel() {
	/* Initialization tile map: */
	SetBackgroundTexture("Data/Map.png");
	/* Initialization border map: */
	SetBorderTexture("Data/Map_border.png", 50);

	this->Player_ = new RedTank(1, 200, 200);
	this->AddPlayerObject(Player_);
	this->SetWatchObject(Player_);

	TankObject* tank;
	for (int i = 0; i < 50; i++) {
		tank = new RedTank(1, 300, 400);
		this->AddEnemyObject(tank);
	}


}

int GameLevel::NextLevel() {
	return BaseLevel::NextLevel();
}

bool GameLevel::ExitGame() {
	return BaseLevel::ExitGame();
}
