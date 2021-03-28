#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <list>
#include <sstream>
#include "ready_objects.h"
#include "settings.h"


class BaseLevel {
private:

	unsigned int count_id_objects_ = 1;

	//all level objects:
	std::vector <UiObject*> Ui_objects_;
	UiObject* Focused_object;
	std::vector <GameObject*> Static_objects_;
	std::vector <TankObject*> Enemy_objects_;
	std::vector <float> enemy_shot_time_; // for shooting enemy
	std::vector <TankObject*> Players_objects_;
	std::list <MovebleObject*> Shot_objects_;
	GameObject* Bonus_object_;


	std::list <GameObject*> All_objects_;

	//die game objects (exist in other vectors).
	std::list <GameObject*> Dies_objects_;

	std::list <BaseObject*> Need_sync_with_client_objects_;

	//level size
	int size_level_height_, size_level_width_, size_level_border_ = 0;

	float min_distance_respawn_to_Static_objects_ = 0.001f; //% size level
	float min_distance_respawn_to_Enemy_objects_ = 0.005f; //% size level
	float min_distance_respawn_to_Players_objects_ = 0.001f; //% size level
	float min_distance_respawn_to_Shot_objects_ = 0.0000010f; //% size level

	VisibleObject* Watch_object_;

	sf::View Player_camera_;

	//background and border:
	sf::Texture Texture_background_;
	sf::Sprite Sprite_background_;
	sf::Texture Texture_border_;
	sf::Sprite Sprite_border_;

	//background music:
	sf::Music music_background_;

	float max_safe_distance = 0;

	void CameraControl();

	bool SafePointSpawn(GameObject* Game_object);
	bool RespawnObject(GameObject* Game_object); ///recreate??? very hard//////////////////
public:
	BaseLevel();
	sf::View& Draw(sf::RenderWindow& window);
	
	bool AddUiObject(UiObject* Ui_object);
	bool AddStaticObject(GameObject* Static_objects, 
		bool const& ignore_random_spawn = false);
	bool AddEnemyObject(TankObject* Enemy_objects,
		bool const& ignore_random_spawn = false);
	bool AddPlayerObject(TankObject* Player_objects,
		bool const& ignore_random_spawn = false);
	bool AddShotObject(MovebleObject* Shot_objects);
	bool AddDieObject(GameObject* Dies_objects);
	bool SetWatchObject(VisibleObject* Watch_object);
	bool SetBonusObject(GameObject* Bonus_object);

	void SetBackgroundTexture(std::string texture_address);
	void SetBorderTexture(std::string texture_address, int const& size_level_border);
	void SetBackgroundMusic(std::string music_address, float const& volume);

	sf::Packet GetPacketToSendAllClient(bool const& all_data = false);	
	void RecvPacketFromServer(sf::Packet& Packet);
	int AddPlayerFromLan(); //return his watchings object

	virtual bool InputKeyboard(int const& player_nuber, sf::Keyboard::Key Key);
	virtual bool InputMouse(sf::Event::EventType event_type, sf::Vector2i mouse_position); 

	void InputEnemy();

	virtual bool UpdateState(float& game_timer);
	void CalculateCollisionOnLevel();

	virtual int NextLevel();
	virtual bool ExitGame();
	~BaseLevel();
};


class GameLevel : public BaseLevel {
private:
	TankObject* Player_;
	UiObject* Point_current_, * Life_, * Speed_, * Rotation_speed_, * Speed_shot_,
		* Shot_distance_, * Time_to_next_shot_, * Shot_life_;

	template <class TypeObject> void SpawnStaticObject(TypeObject* object, int const& quantity,
		int const& id_object, float const& spawn_x, float const& spawn_y);

	template <class TypeObject> void SpawnEnemyObject(TypeObject* object, int const& quantity,
		int const& id_object, float const& spawn_x, float const& spawn_y);

public:
	GameLevel(bool const& is_server = true);
	
	bool UpdateState(float& game_timer) override;

	int NextLevel() override;
	bool ExitGame() override;
};