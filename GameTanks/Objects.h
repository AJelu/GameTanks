#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include "collisions.h"
#include "bonuses.h"
#include "settings.h"

//this objects using in levels to create game experience: game menu, game levels

class BaseObject{
private:
	//For synchronize by lan:
	int id_object_; 
	bool need_synch_by_lan_;

public:
	BaseObject();
	BaseObject(int const& id_object);

	int GetIdObject();
	void SetIdObject(int const& id_object);

	virtual std::string ClassName();
	virtual bool CreatePacket(sf::Packet& Packet); // set parameters in packed
	virtual bool SetDataFromPacket(sf::Packet& Packet); // get parameters from packed

	bool GetNeedSynchByLan();
	virtual void SetNeedSynchByLan(bool const& need_synch_by_lan);

	virtual ~BaseObject();
};

class VisibleObject : public BaseObject {
private:
	static std::vector<std::string> Texture_name_;
	static std::vector<sf::Texture*> Texture_objects_;

	sf::Texture* GetTexture(std::string texture_name);

	sf::Vector2f offset_sprite_coordinate_;

	//For animations:
	int tile_level_, tile_frame_current_; //current tile (now showing)
	int animation_frame_start_, animation_frame_end_;
	bool looped_; //animate autorestart
	float animation_speed_for_frame_; // time for one frame (1000 = 1s)
	float current_frame_animation_time_;

	bool ShowTile(); //show current frame texture
	bool SetTile(int const& tile_level, int const& tile_number);
	
	//Animate buffer(queue):
	std::vector<int> q_tile_level_, q_animation_frame_start_, q_animation_frame_end_;
	std::vector<float> q_animation_speed_for_frame_;

	int frame_count_x_, frame_count_y_;
	sf::Texture* Texture_object_;
	sf::Sprite Sprite_object_;

	float vector_rotate_x_, vector_rotate_y_;
	bool RecalculateVector();

	//For return previous state:
	float previous_vector_rotate_x_, previous_vector_rotate_y_;
	sf::Vector2f previous_position_centre_;

	//For optimization:
	float gradus_ = 0;
	float previous_gradus_ = 0;

public:
	VisibleObject();
	VisibleObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture, int const& frame_count_x, int const& frame_count_y);

	static void DestroyCreatedStaticVectors();

	float CalculateGradus();

	//Animations:
	void ClearAnimarionList(bool const& all = false);
	void StartPlayAnimation(int const& tile_level, 
		int const& frame_start, int const& frame_end,
		float const& animation_speed_for_frame = 1000, bool const& looped = false);
	bool AnimationEnd(bool const& all_list = false);

	//For recalculate animations:
	virtual void RecalculateState(float const& game_time);

	//Get object parameters:
	const sf::Vector2f& GetCoordinateCentre();
	const sf::Vector2f GetOffsetSprite(bool get_scale_size = false);
	int GetHeightSprite(bool get_scale_size = false);
	int GetWidthSprite(bool get_scale_size = false);
	float GetVectorX();
	float GetVectorY();

	//For return previous state:
	void RestorePreviousState(); 
	void SafeState();

	//Set for vector:
	void SetRotationVector(float const& vector_x, float const& vector_y);
	void VectorRotation(float const& rotation_degree);
	void SetRotation(float const& rotation_by_gradus);
	sf::Vector2f ChangeVectorByDirection(sf::Vector2f const& vector);

	//For objective's move
	void SetCoordinate(sf::Vector2f const& coordinate_centre);
	void MoveByVector(float const& length_move);
	float GetDistanceToPoint(const sf::Vector2f& point);

	//For lan:
	std::string ClassName() override;
	bool CreatePacket(sf::Packet& Packet) override;
	bool SetDataFromPacket(sf::Packet& Packet) override;

	//Texture painting processing:
	bool SetTexture(std::string const& texture,
						int const& frame_count_x, int const& frame_count_y);
	void SetOffsetSprite(sf::Vector2f const& offset_sprite_coordinate);
	void SetScale(sf::Vector2f const& vector_scale);
	const sf::Vector2f GetScale();

	virtual void Draw(sf::RenderWindow& window);
	~VisibleObject() override;
};

class AudioObject : public VisibleObject {
private:
	static std::vector<std::string> Audio_file_name_;
	static std::vector<sf::SoundBuffer*> Sounds_buffer_;

	sf::SoundBuffer* GetSoundsBuffer(std::string audio_file);

	//All audio action:
	std::vector <std::string> Audio_action_name_;
	std::vector <std::string> Audio_action_file_name_;
	std::vector <bool> Audio_action_looped_;
	std::vector <float> Audio_action_volume;

	//Playing sounds:
	std::vector <std::string> Audio_action_playing_name_;
	std::vector <sf::Sound*> Sounds_file_;

	//Queues for start and stop play sound:
	std::queue <std::string> Start_audio_action_;
	std::queue <std::string> Stop_audio_action_;

	//For lan:
	std::list <int> Need_send_start_to_lan_;
	std::list <int> Need_send_stop_to_lan_;

	sf::View* Camera_;

	bool PlayAudioAction(bool const& play, std::string const& audio_action);
	bool StopPlayingAudioAction(std::string const& audio_action);

public:
	AudioObject();
	AudioObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture, int const& frame_count_x, int const& frame_count_y);
	
	static void DestroyCreatedStaticVectors();
	
	void AddAudioAction(std::string const& audio_action_name,
		std::string const& audio_file, bool looped = false, float const& volume = 100);

	bool StartAudioAction(std::string const& audio_action);
	bool StopAudioAction(std::string const& audio_action);

	bool PlaysSounds();
	void StopAllSounds();

	//For playing audio actions:
	void RecalculateState(float const& game_time) override;

	void SetCamera(sf::View* Camera);
	sf::View* GetCamera();

	//For lan:
	std::string ClassName() override;
	bool CreatePacket(sf::Packet& Packet) override;
	bool SetDataFromPacket(sf::Packet& Packet) override;
	void SetNeedSynchByLan(bool const& need_synch_by_lan) override;

	~AudioObject() override;
};

class UiObject : public AudioObject {
private:
	bool enter_on_this_, leave_on_this_, down_on_this_, up_on_this_;
	std::string text_;

	sf::Vector2f coordinate_centre_;
	VisibleObject* Anchor_object_;
	sf::Font Font_;
	sf::Text Text_in_ui_;
	sf::Color Text_color_;
	sf::Text::Style Text_style_;
	unsigned int character_size_;
	float cursor_size_;

	bool focusable_;
	float time_blink_cursor_ = 0;
	bool show_cursor_;

	enum class Object_centring {
		LEFT = 1,
		RIGHT = 2,
		CENTER = 3,
		TOP = 4,
		MIDDLE = 5,
		BOTTOM = 6
	};

	Object_centring centring_x;
	Object_centring centring_y;

	float text_centre_ = 0; //text_centre_ < 0: left; > 0: right; = 0: centre;

public:
	UiObject();
	UiObject(
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture, int const& frame_count_x, int const& frame_count_y);
	
	bool MouseInputToObject(sf::Event::EventType const& event_type, 
		sf::Vector2i const& mouse_position, bool keyboard_input = false);
	void InputKey(sf::Keyboard::Key const& key);
	
	//Cursor blink:
	void RecalculateState(float const& game_time) override;

	//Sets:
	void SetText(std::string text, bool const& add_to_previous = false);
	void ShowCursorBlink(bool const& show_cursor);
	void SetTextColor(sf::Color const& Text_color);
	void SetTextStyle(sf::Text::Style const& Text_style);
	void SetCharacterSize(unsigned int const& character_size);
	void SetCursorSize(float const& cursor_size);
	void SetFocusable(bool const& focusable);
	void SetTextAlign(float const& align);

	void SetStartCoorditateLeft();
	void SetStartCoorditateRight();
	void SetStartCoorditateCentre();
	void SetStartCoorditateTop();
	void SetStartCoorditateMiddle();
	void SetStartCoorditateBottom();

	//Gets:
	std::string GetText();
	bool GetCursorBlink();
	sf::Color GetTextColor();
	sf::Text::Style GetTextStyle();
	unsigned int GetCharacterSize();
	float GetCursorSize();
	bool GetFocusable();
	float GetTextAlign();

	bool GetMouseDownOnThis(bool clear = false);
	bool GetMouseUpOnThis(bool clear = false);
	
	void SetAnchorObject(VisibleObject* Anchor_object);
	VisibleObject* GetAnchorObject();

	virtual void ActionEnter();
	virtual void ActionLeave();
	virtual void ActionClickDown();
	virtual void ActionClickUp();

	void Draw(sf::RenderWindow& window) override;
};

class GameObject : public AudioObject {
private:
	int life_level_, max_life_level_, base_point_, current_point_;
	float max_collision_distance_;
	bool collision_off_;
	static bool display_collision_;
	
	int game_type_ = 0;

	float time_to_respawn_;

	std::vector <RoundCollision*> Collisions_;

	GameObject* Parrent_;

	//Temp variable:
	sf::Vector2f Point_1_, Point_2_;

public:
	GameObject();
	GameObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture, int const& frame_count_x, int const& frame_count_y,
		int const& max_life_level, GameObject* Parrent = nullptr);

	void SetBasePoint(int const& base_point);
	void SetCurrentPoint(int const& current_point, bool const& add_to_previous = true);
	void SetLifeLevel(int const& life_level, bool const& add_to_previous = false);
	void SetMaxLifeLevel(int const& max_life_level);
	void SetTimeToRespawn(float const& time_to_respawn, 
		bool const& add_to_previous = false);
	
	int GetBasePoint();
	int GetCurrentPoint();
	int GetLifeLevel();
	int GetMaxLifeLevel();
	float GetTimeToRespawn();
	float GetSafeDistance();
	GameObject* GetPerrent();

	static bool DisplayCollision(bool const& display_collision);

	void RestoreLife();

	//For recalculate time to respawn:
	void RecalculateState(float const& game_time) override;

	//For collisions:
	void AddCollision(RoundCollision* New_colision);
	bool ObjectInRangeLevel(int level_size_x, int level_size_y, int level_size_border);
	float SafeDistanceToCollision(GameObject* Game_object);
	bool Collision(GameObject* Game_object);

	void CollisionOff(); //Ignore all collisions
	void CollisionOn();

	int GetGameType();
	void SetGameType(int const& game_type);

	//For animation:
	virtual void ActionDie(); //need override in daughter
	virtual void ActionChangeLifeLevel(int const& life_level); //need override in daughter
	virtual void ActionLife(); //need override in daughter

	//For lan:
	std::string ClassName() override;
	bool CreatePacket(sf::Packet& Packet) override;
	bool SetDataFromPacket(sf::Packet& Packet) override;

	void Draw(sf::RenderWindow& window) override;
	~GameObject() override;
};

class MovebleObject : public GameObject {
private:
	float speed_, distance_, freeze_time_; //speed_ - px by second
	float rotation_speed_, rotation_degree_; // rotation_speed_ - gradus by sec
	bool previously_moveed_ = false, previously_rotated_ = false;

public:
	MovebleObject();
	MovebleObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture, int const& frame_count_x, int const& frame_count_y,
		int const& max_life_level, float const& speed, float const& freeze_time,
		float const& rotation_speed, GameObject* Parrent = nullptr);

	//Set object parameters:
	void SetSpeedMove(float const& speed); //px by sec
	void SetFreezeTime(float const& freeze_time); //sec
	void SetDistanceMove(float const& distance, 
		bool const& add_to_previous = false); //px
	void SetRotationDegree(float const& rotation_degree, 
		bool const& add_to_previous = false);
	void SetRotationSpeed(float const& rotation_speed); // gradus by sec

	//Get object parameters:
	float GetSpeedMove(); //px by sec
	float GetDistanceMove(); //px
	float GetFreezeTime(); //sec
	float GetRotationDegree(); //The remainder of the angle of rotation!!!!!!
	float GetRotationSpeed();

	void MoveTo(float const& move_to_x, float const& move_to_y);

	//For recalculate position
	void RecalculateState(float const& game_time) override;

	//For lan:
	std::string ClassName() override;
	bool CreatePacket(sf::Packet& Packet) override;
	bool SetDataFromPacket(sf::Packet& Packet) override;

	//For animation:
	virtual void ActionStartMove(); //need override in daughter
	virtual void ActionMoving(float const& distance); //need override in daughter
	virtual void ActionEndMove(); //need override in daughter
	virtual void ActionStartRotate(); //need override in daughter
	virtual void ActionRotating(float const& rotation_degree); //need override in daughter
	virtual void ActionEndRotate(); //need override in daughter
};

class TankObject : public MovebleObject {
private:
	float speed_shot_, shot_distance_, time_to_next_shot_, time_freeze_shot_;
	sf::Vector2f Point_create_shot_;
	int shot_life_;

	Bonuses* Bonus_;
	void DeleteBonusFromObject(Bonuses * bonus);
	void AddBonusToObject(Bonuses * bonus);

protected:
	virtual MovebleObject* Shot();

public:
	TankObject();
	TankObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture, 
		int const& frame_count_x, int const& frame_count_y,
		int const& max_life_level,
		float const& speed, float const& freeze_time,
		float const& rotation_speed, sf::Vector2f const& point_create_shot_by_vector, 
		int const& shot_life, float const& speed_shot, float const& shot_distance,
		float const& time_freeze_shot, 
		GameObject* Parrent);

	void AddBonus(Bonuses* bonus);
	Bonuses* GetBonus();

	bool CanCreateShot();
	MovebleObject* CreateShot(bool const& forcibly_shot = false);
	void RecalculateState(float const& game_time) override;

	void MoveUp(float const& value = 10);
	void MoveDown(float const& value = 10);
	void MoveRight(float const& value = 10);
	void MoveLeft(float const& value = 10);

	sf::Vector2f GetPointCreateShot();
	float GetSpeedShot();
	int GetLifeShot();
	float GetShotDistance();
	float GetTimeToNextShot();
	float GetTimeFreezeShot();

	void SetPointCreateShot(sf::Vector2f const& point_create_shot);
	void SetSpeedShot(float const& speed_shot);
	void SetLifeShot(int const& shot_life);
	void SetShotDistance(float const& shot_distance);
	void SetTimeToNextShot(float const& time_to_next_shot);
	void SetTimeFreezeShot(float const& time_freeze_shot);

	//For lan:
	std::string ClassName() override;
	bool CreatePacket(sf::Packet& Packet) override;
	bool SetDataFromPacket(sf::Packet& Packet) override;
};