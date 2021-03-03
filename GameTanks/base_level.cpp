#include "levels.h"

bool BaseLevel::CalculateCollisionOnLevel()
{
	return false;
}

BaseLevel::BaseLevel()
{
	/* Initialization tile map: */
	Texture_background_.loadFromFile("Data/Map.png");
	Sprite_background_.setTexture(Texture_background_);
	Sprite_background_.setPosition(0, 0);

	Player_client = TankObject(1, 
		sf::Vector2f(200, 200), sf::Vector2f(60, 157), 
		"Data/Tank4.png", 
		5, 2, 1,   200  , 0, 20 , 1000, 200, 500);
}

void BaseLevel::Draw(RenderWindow& window)
{
	window.draw(Sprite_background_);
	Player_client.Draw(window, nullptr);
}

void BaseLevel::AddUiObject(UiObject Ui_object)
{
}

void BaseLevel::AddStatisObject(GameObject Static_objects)
{
}

void BaseLevel::AddEnemyObject(TankObject Enemy_objects)
{
}

void BaseLevel::AddShotObject(MovebleObject Shot_objects)
{
}

BaseObject* BaseLevel::GetObjectToSendClient()
{
	return nullptr;
}

void BaseLevel::RecvObjectFromServer()
{
}

bool BaseLevel::InputKeyboard(bool for_client, sf::Keyboard::Key Key)
{
	if (Key == Keyboard::Up) {
		Player_client.MoveUp();
		Player_client.StartPlayAnimation(1, 1, 5, 50, true);
	}
	if (Key == Keyboard::Down) {
		Player_client.MoveDown();
		Player_client.StartPlayAnimation(2, 1, 5, 70, true);
	}
	if (Key == Keyboard::Left) {
		Player_client.MoveLeft();
	}
	if (Key == Keyboard::Right) {
		Player_client.MoveRight();
	}
	return false;
}

bool BaseLevel::InputMouse(sf::Event::EventType event_type, sf::Vector2i mpuse_position)
{
	return false;
}

void BaseLevel::InputEnemy()
{
}

bool BaseLevel::UpdateState(float& game_timer)
{
	Player_client.RecalculateState(game_timer);
	Player_client.ForAnimation(game_timer);
	return false;
}

int BaseLevel::NextLevel()
{
	return 0;
}

bool BaseLevel::ExitGame()
{
	return false;
}

BaseLevel::~BaseLevel()
{
}
