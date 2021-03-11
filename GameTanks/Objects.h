#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "collisions.h"

//this objects using in levels to create game experience: game menu, game levels


class BaseObject{
private:
	int id_object_; //for synchronize by lan

public:
	BaseObject();
	BaseObject(int const& id_object);

	//get object parameters
	int GetIdObject();

	virtual ~BaseObject();
};

class AudioObject : public BaseObject{
private:
	std::vector <std::string> audio_action_name_;
	std::vector <sf::Sound*> sounds_file_;
	std::vector <sf::SoundBuffer*> sounds_buffer_;
	std::vector <int> sounds_volume_;
public:
	AudioObject();
	AudioObject(int const& id_object);
	void AddAudioAction(std::string const& audio_action_name,
						std::string const& audio_file, int const& volume = 100);
	bool StartAudioAction(std::string const& audio_action, bool looped = false);
	bool StopAudioAction(std::string const& audio_action);
	~AudioObject() override;
};

class VisibleObject : public AudioObject{
private:
	bool need_redraw_image_; //using for redraw screen. if have changing - true

	sf::Vector2f offset_sprite_coordinate_;

	//for animates
	int tile_level_, tile_frame_current_; //current tile (now showing); 1..x
	int animation_frame_start_, animation_frame_end_; //animation frames start and end; 1..x
	bool looped_; //animate autorestart
	float animation_speed_for_frame_; // time for one frame; 1000 = 1s
	float current_frame_animation_time_; // time for current frame

	int frame_count_x_, frame_count_y_; // count frame on texture 1..x
	sf::Texture Texture_object_;
	sf::Sprite Sprite_object_;

	float vector_rotate_x_, vector_rotate_y_;

	//for return previous state
	float previous_vector_rotate_x_, previous_vector_rotate_y_;
	sf::Vector2f previous_position_centre_;

	//for optimization:
	float gradus_ = 0; //float CalculateGradus();
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
	void StartPlayAnimation(int const& tile_level, 
		int const& frame_start, int const& frame_end,
		float const& animation_speed_for_frame = 1000, bool const& looped = false);
	bool AnimationEnd();
	void ForAnimation(float const& game_time); //counting current frame

	//get object parameters
	bool GetNeedRedrawImage(); //return true if need update image
	const sf::Vector2f& GetCoordinateCentre();
	const sf::Vector2f& GetOffsetSprite();
	int GetHeightSprite();
	int GetWidthSprite();
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

	virtual void Draw(sf::RenderWindow& window);
};

class UiObject : public VisibleObject {
private:
	bool focus_on_this_, down_on_this_, up_on_this_;
	std::string text_;

	sf::Vector2f coordinate_centre_;
	sf::View* Camera_;
public:
	UiObject();
	UiObject(int const& id_object,
		sf::Vector2f const& coordinate_centre, sf::View* Camera,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture, int const& frame_count_x, int const& frame_count_y);
	bool IsFocusOnThis(int const& x, int const& y);
	bool IsDownOnThis(int const& x, int const& y);
	bool IsUpOnThis(int const& x, int const& y);
	void AddInputText(std::string const& text);
	void SetText(std::string const& text);

	bool GetFocusOnThis(bool clear = false);
	bool GetDownOnThis(bool clear = false);
	bool GetUpOnThis(bool clear = false);
	std::string GetText();

	void Draw(sf::RenderWindow& window) override;
};

class Button : public UiObject {
public:

};


class GameObject : public VisibleObject {
private:
	int life_level_;
	float max_collision_distance_;
	bool collision_off_;

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
		int const& life_level, GameObject* Parrent = nullptr);

	void SetLifeLevel(int const& life_level, bool const& add_to_previous = false);
	void SetTimeToRespawn(float const& time_to_respawn, bool const& add_to_previous = false);
	int GetLifeLevel();
	float GetTimeToRespawn();
	float GetSafeDistance();
	GameObject* GetPerrent();

	virtual void RestoreLife();

	//for recalculate time to respawn
	virtual void RecalculateState(float const& game_time);

	//for collisions
	void AddCollision(RoundCollision* New_colision);
	bool ObjectInRangeLevel(int level_size_x, int level_size_y, int level_size_border);
	float SafeDistanceToCollision(GameObject* Game_object);
	bool Collision(GameObject* Game_object, bool healt = false);

	void CollisionOff();//ignore all collisions
	void CollisionOn();

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
		int const& life_level, float const& speed, float const& freeze_time, 
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
	float speed_shot_, shot_distance_, time_to_next_shot_, time_freeze_shot_, point_create_shot_;
protected:
	virtual MovebleObject* Shot();
public:
	TankObject();
	TankObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture, 
		int const& frame_count_x, int const& frame_count_y,
		int const& life_level,
		float const& speed, float const& freeze_time,
		float const& rotation_speed, int const& point_create_shot_by_vector, 
		float const& speed_shot, float const& shot_distance, float const& time_freeze_shot, 
		GameObject* Parrent);

	bool CanCreateShot();
	MovebleObject* CreateShot(bool const& forcibly_shot = false);
	void RecalculateState(float const& game_time) override; //+recalculate time_to_next_shot

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();

	int GetPointCreateShot();
	float GetSpeedShot();
	float GetShotDistance();
	float GetTimeToNextShot();
	float GetTimeFreezeShot();

	void SetPointCreateShot(int const& point_create_shot);
	void SetSpeedShot(float const& speed_shot);
	void SetShotDistance(float const& shot_distance);
	void SetTimeToNextShot(float const& time_to_next_shot);
	void SetTimeFreezeShot(float const& time_freeze_shot);
};