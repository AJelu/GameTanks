#include "Levels.h"

GameLevel::GameLevel() : BaseLevel() {
	/* Initialization tile map: */
	SetBackgroundTexture("Data/Map.png");
	SetBorderTexture("Data/Map_border.png", 50);

	this->Player_ = new RedTank(1, 200, 200);
	this->AddPlayerObject(Player_);
	this->SetWatchObject(Player_);
	this->AddPlayerObject(new RedTank(1, 900, 200));

	TankObject* tank;
	for (int i = 0; i < 20; i++) {
		tank = new RedTank(1, 300, 400);
		this->AddEnemyObject(tank);
	}

	this->AddStaticObject(new GameObject(2,
		sf::Vector2f(200, 600), sf::Vector2f(108, 124),
		"Data/BoomTest2.png", 
		36, 1, 1));
	this->AddStaticObject(new GameObject(2,
		sf::Vector2f(400, 600), sf::Vector2f(57, 57),
		"Data/BoomTest3.png",
		48, 1, 1));
	this->AddStaticObject(new GameObject(2,
		sf::Vector2f(600, 600), sf::Vector2f(115, 115),
		"Data/BoomTest5.png",
		22, 1, 1));


	/* Initialization border map: */
}

int GameLevel::NextLevel() {
	return BaseLevel::NextLevel();
}

bool GameLevel::ExitGame() {
	return BaseLevel::ExitGame();
}
