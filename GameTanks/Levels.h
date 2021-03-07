#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ready_objects.h"
#include "settings.h"

using namespace sf;

class BaseLevel
{
private:
	//all level objects:
	std::vector <UiObject*> Ui_objects_;
	std::vector <GameObject*> Statis_objects_;
	std::vector <TankObject*> Enemy_objects_;
	std::vector <TankObject*> Players_objects_;
	std::vector <MovebleObject*> Shot_objects_;

	//die game objects (exist in other vectors).
	std::vector <GameObject*> Dies_objects_;

	std::vector <BaseObject*> Need_sync_with_client_objects_;

	//list game  die objects
	int size_level_height_, size_level_width_;

	VisibleObject* Watch_object_;

	View Player_camera;

	//background and border:
	Texture Texture_background_;
	Sprite Sprite_background_;
	Texture Texture_border_;
	Sprite Sprite_border_;

	void CalculateCollisionOnLevel(); 
	void CameraControl();
public:
	BaseLevel();
	View& Draw(RenderWindow& window); ////////////////
	
	void AddUiObject(UiObject* Ui_object);
	void AddStatisObject(GameObject* Static_objects);
	void AddEnemyObject(TankObject* Enemy_objects);
	void AddPlayerObject(TankObject* Player_objects);
	void AddShotObject(MovebleObject* Shot_objects);

	void SetWatchObject(VisibleObject* Watch_object);
	void SetBackgroundTexture(string texture_address);
	void SetBorderTexture(string texture_address);

	BaseObject* GetObjectToSendClient();
	
	void RecvObjectFromServer();

	virtual bool InputKeyboard(int player_nuber, sf::Keyboard::Key Key);
	virtual bool InputMouse(sf::Event::EventType event_type, sf::Vector2i mouse_position); 

	void InputEnemy();

	bool UpdateState(float& game_timer); 

	int NextLevel();
	bool ExitGame();
	~BaseLevel();
};

class GameLevel : public BaseLevel {
private:
	TankObject* Player_;
public:
	GameLevel();
};