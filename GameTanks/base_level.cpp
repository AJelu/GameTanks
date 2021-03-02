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

	Player_client = TankObject(1, sf::Vector2f(0, 0), sf::Vector2f(0, 0), "1", 1, 1, 1, 1, 1, 0, 0, 0);
}

void BaseLevel::Draw(RenderWindow& window)
{
	window.draw(Sprite_background_);
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
