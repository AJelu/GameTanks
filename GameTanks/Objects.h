#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "collisions.h"

using namespace std;
using namespace sf;

//this objects using in levels to create game experience: game menu, game levels




class BaseObject //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
{
private:
	int id_object_; //for synchronize by lan

public:
	BaseObject();
	BaseObject(int const& id_object);

	//get object parameters
	int GetIdObject();

	virtual ~BaseObject();
};

class AudioObject : public BaseObject //Ready
{
private:
	vector <string> audio_action_name_;
	vector <Sound*> sounds_file_;
	vector <SoundBuffer*> sounds_buffer_;
	vector <int> sounds_volume_;
public:
	AudioObject();
	AudioObject(int const& id_object);
	void AddAudioAction(string const& audio_action,
						string const& audio_file, int const& volume = 100);
	bool StartAudioAction(string const& audio_action, bool looped = false);
	bool StopAudioAction(string const& audio_action);
	~AudioObject() override;
};

class VisibleObject : public AudioObject //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
{
private:
	bool need_redraw_image_; //using for redraw screen. if have changing - true

	sf::Vector2f offset_sprite_coordinate_;

	//for animates
	int tile_level_, tile_frame_current_; //current tile (now showing); 1..x
	int animation_frame_start_, animation_frame_end_; //animation frames start and end; 1..x
	bool looped_; //animate autorestart
	float animation_speed_for_frame_; // time for one frame; 1000 = 1s
	float current_frame_animation_time_; // time for current frame


	//float current_frame_; /////////////

	int frame_count_x_, frame_count_y_; // count frame on texture 1..x
	Texture Texture_object_;
	Sprite Sprite_object_;

	float vector_rotate_x_, vector_rotate_y_;

	void SetNeedRedrawImage();
	bool RecalculateVector();
	bool ShowTile(); //show current frame texture
	bool SetTile(int const& tile_level, int const& tile_number); //set show choosed frame texture
public:
	VisibleObject();
	VisibleObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		string const& texture, int const& frame_count_x, int const& frame_count_y);

	void StartPlayAnimation(int const& tile_level, 
		int const& frame_start, int const& frame_end,
		float const& animation_speed_for_frame = 1000, bool const& looped = false);
	bool AnimationEnd();
	void ForAnimation(float const& game_time); //counting current frame

	//get object parameters
	bool GetNeedRedrawImage(); //return true if need update image
	sf::Vector2f GetCoordinateCentre();
	sf::Vector2f GetOffsetSprite();
	int GetHeightSprite();
	int GetWidthSprite();
	float GetVectorX();
	float GetVectorY();

	//set object parameters
	void SetRotationVector(float const& vector_x, float const& vector_y);
	void RotationVector(int const& rotation_degree);
	void SetRotation(float const& rotation_by_gradus);

	void SetCoordinate(sf::Vector2f const& coordinate_centre);
	void SetTexture(string const& texture, 
						int const& frame_count_x, int const& frame_count_y);
	void SetOffsetSprite(sf::Vector2f const& offset_sprite_coordinate);

	void Draw(sf::RenderWindow& window, 
				View const& Player_camera, bool const& plus_offset_camera = false);
};

class UiObject : public VisibleObject
{
private:
	bool focus_on_this_, down_on_this_, up_on_this_;
	string text_;

public:
	UiObject();
	UiObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		string const& texture, int const& frame_count_x, int const& frame_count_y);
	bool IsFocusOnThis(int const& x, int const& y);
	bool IsDownOnThis(int const& x, int const& y);
	bool IsUpOnThis(int const& x, int const& y);
	void AddInputText(string const& text);
	void SetText(string const& text);


	bool GetFocusOnThis();
	bool GetDownOnThis();
	bool GetUpOnThis();
	string GetText();
};

class Button : public UiObject
{
public:

};

//others ui objects



class GameObject : public VisibleObject //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
{
private:
	int life_level_;
	vector <RoundCollision*> collisions_;

public:
	GameObject();
	GameObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		string const& texture, int const& frame_count_x, int const& frame_count_y,
		int const& life_level);

	void SetLifeLevel(int const& life_level);
	int GetLifeLevel();
	void AddCollision(RoundCollision* const& new_colision);
	float DistanceToCollision(GameObject* const& game_object);
	~GameObject() override;
};


class MovebleObject : public GameObject //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
{
private:
	float speed_, distance_, freeze_time_;
	int rotation_degree_;
public:
	MovebleObject();
	MovebleObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		string const& texture, int const& frame_count_x, int const& frame_count_y,
		int const& life_level, float const& speed, float const& freeze_time);

	//set object parameters
	void SetSpeed(float const& speed);
	void SetFreezeTime(float const& freeze_time);
	void SetDistance(float const& distance, bool const& add_to_previous = false);

	//get object parameters
	float GetSpeed();
	float GetDistance();
	float GetFreezeTime();

	void MoveTo(int const& move_to_x, int const& move_to_y);

	//for recalculate position ((vector+speed+distance)*timer), vector rotate
	virtual void RecalculateState(float const& game_time);

	//for heal collisions
	void TerminateCollision(GameObject const& game_object);
	void TerminateCollision(MovebleObject const& moveble_object);
};

class TankObject : public MovebleObject //++++++++++++++++++++++++++++++++++++
{
private:
	float speed_shot_, shot_distance_, time_to_next_shot_, time_freeze_shot_;

protected:
	virtual MovebleObject* Shot();
public:
	TankObject();
	TankObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		string const& texture, int const& frame_count_x, int const& frame_count_y,
		int const& life_level, float const& speed, float const& freeze_time,
		float const& speed_shot, float const& shot_distance, 
		float const& time_freeze_shot);

	bool CanCreateShot();
	MovebleObject* CreateShot(bool const& forcibly_shot = false);
	void RecalculateState(float const& game_time) override; //+recalculate time_to_next_shot

	float GetSpeedShot();
	float GetShotDistance();
	float GetTimeToNextShot();
	float GetTimeFreezeShot();

	void SetSpeedShot(float const& speed_shot);
	void SetShotDistance(float const& shot_distance);
	void SetTimeToNextShot(float const& time_to_next_shot);
	void SetTimeFreezeShot(float const& time_freeze_shot);
};