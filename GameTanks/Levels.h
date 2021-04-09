#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <list>
#include <sstream>
#include <chrono>
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
	std::list <int> Players_who_need_delete_;
	std::vector <MovebleObject*> Shot_objects_;
	GameObject* Bonus_object_;


	std::list <GameObject*> All_objects_;

	//die game objects (exist in other vectors).
	std::list <GameObject*> Dies_objects_;

	std::vector <sf::Packet> Packet_send_all_data_, 
							 Packet_send_changes_;
	std::list <sf::Packet> Packets_recv_;

	//level size
	int size_level_height_, size_level_width_, size_level_border_ = 0;

	float min_distance_respawn_to_Static_objects_ = 0.001f; //% size level
	float min_distance_respawn_to_Enemy_objects_ = 0.005f; //% size level
	float min_distance_respawn_to_Players_objects_ = 0.01f; //% size level
	float min_distance_respawn_to_Shot_objects_ = 0.0000010f; //% size level

	VisibleObject* Watch_object_;

	sf::View Player_camera_;

	//background and border:
	VisibleObject Background_, Border_;

	//background music:
	sf::Music music_background_;

	float max_safe_distance = 0;

	void CameraControl();

	bool SafePointSpawn(GameObject* Game_object);
	bool RespawnObject(GameObject* Game_object);
	void UnpackingPacket(sf::Packet& Packet);
	void AddAnchorUiToObject(GameObject* Game_object, std::string text);
public:
	BaseLevel();
	sf::View& Draw(sf::RenderWindow& window);
	
	bool AddUiObject(UiObject* Ui_object);
	bool AddStaticObject(GameObject* Static_objects, 
		bool const& ignore_random_spawn = false);
	bool AddEnemyObject(TankObject* Enemy_objects,
		bool const& ignore_random_spawn = false);
	bool AddPlayerObject(TankObject* Player_objects,
		bool const& ignore_random_spawn = false, int need_add_ui_id = 0);
	bool AddShotObject(MovebleObject* Shot_objects);
	bool AddDieObject(GameObject* Dies_objects);
	bool SetWatchObject(VisibleObject* Watch_object);
	bool SetBonusObject(GameObject* Bonus_object,
		bool const& ignore_random_spawn = false);

	void DeleteClientPlayer(int const& number);

	TankObject* GetPlayer(int const& player_number);
	int GetPlayerCount();
	GameObject* GetObjectById(int const& id_object);

	void SetBackgroundTexture(std::string texture_address);
	void SetBorderTexture(std::string texture_address, int const& size_level_border);
	void SetBackgroundMusic(std::string music_address, float const& volume);

	sf::Packet GetPacketToSendAllClient(int const& player_number, 
		bool const& all_data);
	void RecvPacketFromServer(sf::Packet& Packet);
	int AddPlayerFromLan(); //return id his watchings object

	virtual bool InputKeyboard(int const& player_nuber, sf::Keyboard::Key Key, 
		sf::Event::EventType event_type);
	virtual bool InputMouse(sf::Event::EventType event_type, sf::Vector2i mouse_position); 

	void InputEnemy();

	virtual bool UpdateState(float& game_timer);
	void CalculateCollisionOnLevel();

	virtual bool ExitLevel(sf::Packet& Result_level);
	~BaseLevel();

	enum Level_type {
		GAME_LEVEL = 2,
		MENU_LEVEL = 1,
		EXIT = 0
	};

	enum Object_type {
		STATIC = 1,
		ENEMY = 2,
		PLAYER = 3,
		SHOT = 4,
		BONUS = 5
	};
};


class GameLevel : public BaseLevel {
private:
	TankObject* Player_;
	int player_id_ = 0;
	TextLine* Stats_, *Point_board;
	UiObject* Exit_;
	ProgressLine* Progress_life_, * Progress_Shot_;
	
	template <class TypeObject> void SpawnStaticObject(TypeObject* object, int const& quantity,
		int const& id_object, float const& spawn_x, float const& spawn_y);

	template <class TypeObject> void SpawnEnemyObject(TypeObject* object, int const& quantity,
		int const& id_object, float const& spawn_x, float const& spawn_y);

	template <class TypeStatValue>
	void StatsOutput(std::string stat_name, TypeStatValue const& stat_base_value,
		int const& stat_object = nullptr, TankObject* player_object = nullptr,
		float const& initial_base_value = 0, float const& stat_bonus_value = 0);

public:
	GameLevel(int const& id_watch_object = 0);
	
	bool UpdateState(float& game_timer) override;

	bool ExitLevel(sf::Packet& Result_level) override;
};

class MenuLevel : public BaseLevel {
private:
	UiObject* NewGame_, * ConnectToGame_, * ConnectToGameInput_, * Exit_ , * Title_;

public:
	MenuLevel();

	bool UpdateState(float& game_timer) override;

	bool ExitLevel(sf::Packet& Result_level) override;
};

class LoadLevel : public BaseLevel {
public:
	LoadLevel(std::string const& text);
};