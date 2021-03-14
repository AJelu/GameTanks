#include "Levels.h"

GameLevel::GameLevel() : BaseLevel() {
	/* Initialization tile map and border: */
	this->SetBackgroundTexture("Data/Maps/Map.png");
	this->SetBorderTexture("Data/Maps/Map_border.png", 50);

	this->Player_ = new Tank2(1, 200, 200);
	this->AddPlayerObject(Player_);
	this->SetWatchObject(Player_);
	this->AddPlayerObject(new RedTank(1, 1200, 200));
	this->SetBonusObject(new Tank4(1, 500, 500));

	TankObject* tank;
	for (int i = 0; i < 500; i++) {
		tank = new RedTank(1, 300, 400);
		this->AddStaticObject(tank);
	}
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
