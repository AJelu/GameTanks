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


	/* temporarily for the test */
	animation = VisibleObject(2,
		sf::Vector2f(270, 270), sf::Vector2f(165, 189),
		"Data/BoomTest2.png", 
		36, 1);
	/* temporarily for the test */


	/* Initialization border map: */
	Texture_border_.loadFromFile("Data/Map_border.png");
	Sprite_border_.setTexture(Texture_border_);
	Sprite_border_.setPosition(0, 0);
}

View& BaseLevel::Draw(RenderWindow& window)
{
	window.draw(Sprite_background_);
	
	Player_client.Draw(window, nullptr);
	Player_camera.setCenter(Player_client.GetCoordinateCentre().x, 
							Player_client.GetCoordinateCentre().y);

	animation.Draw(window, nullptr); /* temporarily for the test */

	window.draw(Sprite_border_);

	return Player_camera;
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
		animation.StartPlayAnimation(1, 1, 36, 55, true);/* temporarily for the test: 50-80 */
		Player_client.StartPlayAnimation(1, 1, 5, 50, true);
	}
	if (Key == Keyboard::Down) {
		Player_client.MoveDown();
		Player_client.StartPlayAnimation(2, 1, 5, 50, true);
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
	animation.ForAnimation(game_timer); /* temporarily for the test */
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
