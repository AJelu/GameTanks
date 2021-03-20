#include "Levels.h"

GameLevel::GameLevel() : BaseLevel() {
	/* Initialization tile map and border: */
	this->SetBackgroundTexture("Data/Maps/Map.png");
	this->SetBorderTexture("Data/Maps/Map_border.png", 50);

	this->Player_ = new Tank2(1, 200, 200);
	this->AddPlayerObject(Player_);
	this->SetWatchObject(Player_);

	this->SetBonusObject(new Tank4(1, 500, 500));

	TankObject* tank;
	for (int i = 0; i < 100; i++) {
		tank = new RedTank(1, 300, 400);
		this->AddStaticObject(tank);
	}
	for (int i = 0; i < 50; i++) {
		tank = new RedTank(1, 300, 400);
		this->AddEnemyObject(tank);
	}

	UiObject* ui = new UiObject(sf::Vector2f(200, 200), sf::Vector2f(100, 50),
		"Data/Ui/Button1.png", 5, 2);
	this->AddUiObject(ui);
	ui->SetRotation(0);
	ui->SetText("TEST text");
	ui->SetFocusable(true);
	/*ui = new UiObject(sf::Vector2f(0, -30), sf::Vector2f(50, 50),
		"Data/Unit/Tank6.png", 12, 4);
	ui->SetAnchorObject(Player_);
	this->AddUiObject(ui);*/

}

int GameLevel::NextLevel() {
	return BaseLevel::NextLevel();
}

bool GameLevel::ExitGame() {
	return BaseLevel::ExitGame();
}
