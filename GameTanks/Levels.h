#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "objects.h"

using namespace sf;

class BaseLevel
{
private:
	//all level objects:
	std::vector <UiObject*> Ui_objects_;
	std::vector <GameObject*> Statis_objects_;
	std::vector <TankObject*> Enemy_objects_;
	std::vector <MovebleObject*> Shot_objects_;

	//die game objects (exist in other vectors).
	std::vector <MovebleObject*> Dies_objects_;

	std::vector <BaseObject*> Need_sync_with_client_objects_;

	//list game  die objects
	int size_level_height, size_level_width;

	TankObject Player_server;
	TankObject Player_client;

	Texture Texture_background_;
	Sprite Sprite_background_;
	Texture Texture_border_;
	Sprite Sprite_border_;

	bool CalculateCollisionOnLevel(); 
public:
	BaseLevel();
	void Draw(RenderWindow& window); ////////////////
	
	void AddUiObject(UiObject Ui_object);
	void AddStatisObject(GameObject Static_objects);
	void AddEnemyObject(TankObject Enemy_objects);
	void AddShotObject(MovebleObject Shot_objects);

	BaseObject* GetObjectToSendClient();
	
	void RecvObjectFromServer();

	bool InputKeyboard(bool for_client, sf::Keyboard::Key Key); //////////////
	bool InputMouse(sf::Event::EventType event_type, sf::Vector2i mouse_position); ////////////////

	void InputEnemy();

	bool UpdateState(float& game_timer); ////////////////

	int NextLevel();
	bool ExitGame();
	~BaseLevel();
};