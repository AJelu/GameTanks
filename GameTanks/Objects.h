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
	int id_object_; //for synchronize by lan

public:
	BaseObject();
	BaseObject(int const& id_object);

	//get object parameters
	int GetIdObject();

	virtual bool CreatePacket(sf::Packet& Packet);
	virtual bool SetDataFromPacket(sf::Packet& Packet);

	virtual ~BaseObject();
};

class VisibleObject : public BaseObject {
private:
	static std::vector<std::string> Texture_name_;
	static std::vector<sf::Texture*> Texture_objects_;

	sf::Texture* GetTexture(std::string texture_name);

	bool need_redraw_image_; //using for redraw screen. if have changing - true

	sf::Vector2f offset_sprite_coordinate_;

	//for animates
	int tile_level_, tile_frame_current_; //current tile (now showing); 1..x
	int animation_frame_start_, animation_frame_end_; //animation frames start and end; 1..x
	bool looped_; //animate autorestart
	float animation_speed_for_frame_; // time for one frame; 1000 = 1s
	float current_frame_animation_time_; // time for current frame
	//animate bufer (queue)
	std::vector<int> q_tile_level_, q_animation_frame_start_, q_animation_frame_end_;
	std::vector<float> q_animation_speed_for_frame_;

	int frame_count_x_, frame_count_y_; // count frame on texture 1..x
	sf::Texture* Texture_object_;
	sf::Sprite Sprite_object_;

	float vector_rotate_x_, vector_rotate_y_;

	//for return previous state
	float previous_vector_rotate_x_, previous_vector_rotate_y_;
	sf::Vector2f previous_position_centre_;

	//for optimization:
	float gradus_ = 0; //float CalculateGradus();
	float previous_gradus_ = 0; //float CalculateGradus();
	//end for optimization;

	void SetNeedRedrawImage();
	bool RecalculateVector();
	bool ShowTile(); //show current frame texture
	bool SetTile(int const& tile_level, int const& tile_number); //set show choosed frame texture
public:
	VisibleObject();
	VisibleObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture, int const& frame_count_x, int const& frame_count_y);

	float CalculateGradus();
	//animatinos
	void ClearAnimarionList(bool const& all = false);
	void StartPlayAnimation(int const& tile_level, 
		int const& frame_start, int const& frame_end,
		float const& animation_speed_for_frame = 1000, bool const& looped = false);
	bool AnimationEnd(bool const& all_list = false);
	//for recalculate animations
	virtual void RecalculateState(float const& game_time);

	//get object parameters
	bool GetNeedRedrawImage(); //return true if need update image
	const sf::Vector2f& GetCoordinateCentre();
	const sf::Vector2f& GetOffsetSprite(bool get_scale_size = false);
	int GetHeightSprite(bool get_scale_size = false);
	int GetWidthSprite(bool get_scale_size = false);
	float GetVectorX();
	float GetVectorY();

	//for return previous state
	void RestorePreviousState(); 
	void SafeState();

	//vector...
	void SetRotationVector(float const& vector_x, float const& vector_y);
	void VectorRotation(float const& rotation_degree);
	void SetRotation(float const& rotation_by_gradus);
	sf::Vector2f ChangeVectorByDirection(sf::Vector2f const& vector);

	//for move
	void SetCoordinate(sf::Vector2f const& coordinate_centre);
	void MoveByVector(float const& length_move);
	float GetDistanceToPoint(const sf::Vector2f& point);

	//view`s part
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

	std::vector <std::string> audio_action_name_;
	std::vector <sf::Sound*> sounds_file_;
	std::vector <int> sounds_volume_;

	std::queue <std::string> Start_audio_action_;
	std::queue <bool> Start_looped_;

	std::queue <std::string> Stop_audio_action_;

	sf::View* Camera_;

	bool PlayAudioAction(std::string const& audio_action, bool looped = false);
	bool StopPlayingAudioAction(std::string const& audio_action);

public:
	AudioObject();
	AudioObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture, int const& frame_count_x, int const& frame_count_y);
	void AddAudioAction(std::string const& audio_action_name,
		std::string const& audio_file, int const& volume = 100);

	bool StartAudioAction(std::string const& audio_action, bool looped = false);
	bool StopAudioAction(std::string const& audio_action);

	//play started audio actions
	void RecalculateState(float const& game_time) override; /////////////////////////////

	void SetCamera(sf::View* Camera);
	sf::View* GetCamera();

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

	float text_centre_ = 0; // <0 - left; >0 - right; 0 - centre;
public:
	UiObject();
	UiObject(
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture, int const& frame_count_x, int const& frame_count_y);
	
	bool MouseInputToObject(sf::Event::EventType const& event_type, 
		sf::Vector2i const& mouse_position, bool keyboard_input = false);
	void InputKey(sf::Keyboard::Key const& key);
	

	//cursor blink
	void RecalculateState(float const& game_time) override;

	//sets
	void SetText(std::string text, bool const& add_to_previous = false);
	void ShowCursorBlink(bool const& show_cursor);
	void SetTextColor(sf::Color const& Text_color);
	void SetTextStyle(sf::Text::Style const& Text_style);
	void SetCharacterSize(unsigned int const& character_size);
	void SetCursorSize(float const& cursor_size);
	void SetFocusable(bool const& focusable);
	void SetTextAlign(float const& align);

	//gets
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
	
	// methods for keyboard input:
	// set focuseble
	// set down
	// set up
	// get set focuseble
	
	void SetAnchorObject(VisibleObject* Anchor_object);
	VisibleObject* GetAnchorObject();

	virtual void PlayAnimateEnter();
	virtual void PlayAnimateLeave();
	virtual void PlayAnimateClickDown();
	virtual void PlayAnimateClickUp();

	void Draw(sf::RenderWindow& window) override;
};


class GameObject : public AudioObject {
private:
	int life_level_, max_life_level_,
		base_point_, current_point_;
	float max_collision_distance_;
	bool collision_off_;
	
	std::string game_type_ = "";

	float time_to_respawn_;

	std::vector <RoundCollision*> Collisions_;

	GameObject* Parrent_;

	//temp var:
	sf::Vector2f point_1, point_2;//////
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
	void SetTimeToRespawn(float const& time_to_respawn, bool const& add_to_previous = false);
	
	int GetBasePoint();
	int GetCurrentPoint();
	int GetLifeLevel();
	int GetMaxLifeLevel();
	float GetTimeToRespawn();
	float GetSafeDistance();
	GameObject* GetPerrent();

	void RestoreLife();

	//for recalculate time to respawn
	void RecalculateState(float const& game_time) override;

	//for collisions
	void AddCollision(RoundCollision* New_colision);
	bool ObjectInRangeLevel(int level_size_x, int level_size_y, int level_size_border);
	float SafeDistanceToCollision(GameObject* Game_object);
	bool Collision(GameObject* Game_object);

	void CollisionOff();//ignore all collisions
	void CollisionOn();

	std::string GetGameType();//ignore all collisions
	void SetGameType(std::string const& game_type);

	//for animation
	virtual void PlayAnimateDie(); ///need override in daughter
	virtual void PlayAnimateLife(); ///need override in daughter

	~GameObject() override;
};


class MovebleObject : public GameObject {
private:
	float speed_/*px by sec*/, distance_, freeze_time_;
	float rotation_speed_/*gradus by sec*/, rotation_degree_;
public:
	MovebleObject();
	MovebleObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture, int const& frame_count_x, int const& frame_count_y,
		int const& max_life_level, float const& speed, float const& freeze_time,
		float const& rotation_speed, GameObject* Parrent = nullptr);

	//set object parameters
	void SetSpeedMove(float const& speed); //px by sec
	void SetFreezeTime(float const& freeze_time); //sec
	void SetDistanceMove(float const& distance, 
		bool const& add_to_previous = false);//px
	void SetRotationDegree(float const& rotation_degree, 
		bool const& add_to_previous = false);
	void SetRotationSpeed(float const& rotation_speed); // gradus by sec

	//get object parameters
	float GetSpeedMove(); //px by sec
	float GetDistanceMove(); //px
	float GetFreezeTime(); //sec
	float GetRotationDegree(); // the remainder of the angle of rotation
	float GetRotationSpeed();

	void MoveTo(float const& move_to_x, float const& move_to_y);

	//for recalculate position ((vector+speed+distance)*timer), vector rotate
	void RecalculateState(float const& game_time) override;

	//for animation
	virtual void PlayAnimateMovePlus(); ///need override in daughter
	virtual void PlayAnimateMoveMinus(); ///need override in daughter
	virtual void PlayAnimateRotate—lockwise(); ///need override in daughter
	virtual void PlayAnimateRotate—ounterclockwise(); ///need override in daughter
};

class TankObject : public MovebleObject {
private:
	float speed_shot_, shot_distance_, time_to_next_shot_, time_freeze_shot_;
	sf::Vector2f point_create_shot_;
	int shot_life_;

	Bonuses* Bonus_;
	void DeleteBonusFromObject(Bonuses * bonus);
	void AddBonusToObject(Bonuses * bonus);
protected:
	virtual MovebleObject* Shot();
public:
	TankObject();
	TankObject(int const& id_object,//add life shot
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
	void RecalculateState(float const& game_time) override; //+recalculate time_to_next_shot

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();

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
};