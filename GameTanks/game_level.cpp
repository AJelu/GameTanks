#include "Levels.h"

GameLevel::GameLevel() : BaseLevel() {
	/* Initialization tile map and border: */
	this->SetBackgroundTexture("Data/Map.png");
	this->SetBorderTexture("Data/Map_border.png", 50);

	this->Player_ = new RedTank(1, 200, 200);
	this->AddPlayerObject(Player_);
	this->SetWatchObject(Player_);
	this->AddPlayerObject(new RedTank(1, 900, 200)); /* why this additional object ? */

	TankObject* tank;
	for (int i = 0; i < 20; i++) {
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
