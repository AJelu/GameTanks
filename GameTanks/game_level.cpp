#include "Levels.h"

GameLevel::GameLevel() : BaseLevel() {
	/* Initialization tile map and border: */
	this->SetBackgroundTexture("Data/Maps/Map.png");
	this->SetBorderTexture("Data/Maps/Map_border.png", 50);

	this->Player_ = new RedTank(1, 200, 200);
	this->AddPlayerObject(Player_);
	this->SetWatchObject(Player_);

	TankObject* tank;
	for (int i = 0; i < 150; i++) {
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
