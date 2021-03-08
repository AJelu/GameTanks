#include "Levels.h"

GameLevel::GameLevel() : BaseLevel() {
	/* Initialization tile map: */
	SetBackgroundTexture("Data/Map.png");

	this->Player_ = new RedTank(1, 200, 200);
	this->AddPlayerObject(Player_);
	this->SetWatchObject(Player_);
	this->AddPlayerObject(new RedTank(1, 400, 200));

	this->AddEnemyObject(new RedTank(1, 300, 400));
	this->AddEnemyObject(new RedTank(1, 600, 400));

	this->AddStatisObject(new GameObject(2,
		sf::Vector2f(200, 600), sf::Vector2f(108, 124),
		"Data/BoomTest2.png", 
		36, 1, 1));
	this->AddStatisObject(new GameObject(2,
		sf::Vector2f(400, 600), sf::Vector2f(57, 57),
		"Data/BoomTest3.png",
		48, 1, 1));
	this->AddStatisObject(new GameObject(2,
		sf::Vector2f(600, 600), sf::Vector2f(115, 115),
		"Data/BoomTest5.png",
		22, 1, 1));


	/* Initialization border map: */
	SetBorderTexture("Data/Map_border.png");
}