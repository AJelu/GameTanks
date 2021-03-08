#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ready_objects.h"
#include "settings.h"


class BaseLevel
{
private:
	//all level objects:
	std::vector <UiObject*> Ui_objects_;
	std::vector <GameObject*> Static_objects_;
	std::vector <TankObject*> Enemy_objects_;
	std::vector <TankObject*> Players_objects_;
	std::vector <MovebleObject*> Shot_objects_;

	//die game objects (exist in other vectors).
	std::vector <GameObject*> Dies_objects_;

	std::vector <BaseObject*> Need_sync_with_client_objects_;

	//level size
	int size_level_height_, size_level_width_, size_level_border_ = 0;

	float min_distance_respawn_to_Static_objects_ = 0.01f; //% size level
	float min_distance_respawn_to_Enemy_objects_ = 0.10f; //% size level
	float min_distance_respawn_to_Players_objects_ = 0.10f; //% size level
	float min_distance_respawn_to_Shot_objects_ = 0.10f; //% size level

	VisibleObject* Watch_object_;

	sf::View Player_camera_;

	//background and border:
	sf::Texture Texture_background_;
	sf::Sprite Sprite_background_;
	sf::Texture Texture_border_;
	sf::Sprite Sprite_border_;

	void CalculateCollisionOnLevel(); 
	void CameraControl();

	bool SafePointSpawn(GameObject* Game_object);
public:
	BaseLevel();
	sf::View& Draw(sf::RenderWindow& window); ////////////////
	
	void AddUiObject(UiObject* Ui_object);
	void AddStaticObject(GameObject* Static_objects);
	void AddEnemyObject(TankObject* Enemy_objects);
	void AddPlayerObject(TankObject* Player_objects);
	void AddShotObject(MovebleObject* Shot_objects);

	void SetWatchObject(VisibleObject* Watch_object);
	void SetBackgroundTexture(std::string texture_address);
	void SetBorderTexture(std::string texture_address, int const& size_level_border);

	BaseObject* GetObjectToSendClient();
	
	void RecvObjectFromServer();

	virtual bool InputKeyboard(int const& player_nuber, sf::Keyboard::Key Key);
	virtual bool InputMouse(sf::Event::EventType event_type, sf::Vector2i mouse_position); 

	void InputEnemy();

	bool UpdateState(float& game_timer); 

	virtual int NextLevel();
	virtual bool ExitGame();
	~BaseLevel();
};

class GameLevel : public BaseLevel {
private:
	TankObject* Player_;
public:
	GameLevel();

	int NextLevel() override;
	bool ExitGame() override;
};