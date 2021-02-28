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
	BaseObject(int id_object);

	//get object parameters
	int GetIdObject();

	virtual ~BaseObject();
};

class AudioObject : public BaseObject //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
{
private:
	vector <string> audio_action_name_;
	vector <Sound*> sounds_file_;
	vector <SoundBuffer*> sounds_buffer_;
	vector <int> sounds_volume_;
public:
	AudioObject();
	AudioObject(int id_object);
	void AddAudioAction(string audio_action, string audio_file, int volume);
	bool StartAudioAction(string audio_action, bool looped);
	bool StopAudioAction(string audio_action);
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
	bool SetTile(int tile_level, int tile_number); //set show choosed frame texture
public:
	VisibleObject();
	VisibleObject(int id_object,
		sf::Vector2f coordinate_centre,
		sf::Vector2f offset_sprite_coordinate,
		string texture, int frame_count_x, int frame_count_y);

	void StartPlayAnimation(int tile_level, int frame_start, int frame_end,
		float animation_speed_for_frame = 1000, bool looped = false);
	bool AnimationEnd();
	void ForAnimation(float& game_time); //counting current frame

	//get object parameters
	bool GetNeedRedrawImage(); //return true if need update image
	sf::Vector2f GetCoordinateCentre();
	sf::Vector2f GetOffsetSprite();
	int GetHeightSprite();
	int GetWidthSprite();
	float GetVectorX();
	float GetVectorY();

	//set object parameters
	void SetRotationVector(float vector_x, float vector_y);
	void RotationVector(int rotation_degree);
	void SetRotation(float rotation_by_gradus);

	void SetCoordinate(sf::Vector2f coordinate_centre);
	void SetTexture(string texture, int frame_count_x, int frame_count_y);
	void SetOffsetSprite(sf::Vector2f offset_sprite_coordinate);

	void Draw(sf::RenderWindow& window, View& Player_camera, bool plus_offset_camera = false);
};

class UiObject : public VisibleObject
{
private:
	bool focus_on_this_, down_on_this_, up_on_this_;
	string text_;

public:
	UiObject();
	UiObject(int id_object,
		sf::Vector2f coordinate_centre,
		sf::Vector2f offset_sprite_coordinate,
		string texture, int frame_count_x, int frame_count_y);
	bool IsFocusOnThis(int x, int y);
	bool IsDownOnThis(int x, int y);
	bool IsUpOnThis(int x, int y);
	void AddInputText(string text);
	void SetText(string text);


	bool GetFocusOnThis();
	bool GetDownOnThis();
	bool GetUpOnThis();
	string GetText();

	~UiObject() override;
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
	GameObject(int id_object,
		sf::Vector2f coordinate_centre,
		sf::Vector2f offset_sprite_coordinate,
		string texture, int frame_count_x, int frame_count_y,
		int life_level);

	void SetLifeLevel(int life_level);
	int GetLifeLevel();
	void AddCollision(RoundCollision* new_colision);
	float DistanceToCollision(GameObject* game_object);
	~GameObject() override;
};


class MovebleObject : public GameObject //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
{
private:
	float speed_, distance_, freeze_time_;
	int rotation_degree_;
public:
	MovebleObject();
	MovebleObject(int id_object,
		sf::Vector2f coordinate_centre,
		sf::Vector2f offset_sprite_coordinate,
		string texture, int frame_count_x, int frame_count_y,
		int life_level, float speed, float freeze_time);

	//set object parameters
	void SetSpeed(float speed);
	void SetFreezeTime(float freeze_time);
	void SetDistance(float distance, bool add_to_previous = false);

	//get object parameters
	float GetSpeed();
	float GetDistance();
	float GetFreezeTime();

	void MoveTo(int move_to_x, int move_to_y);

	//for recalculate position ((vector+speed+distance)*timer), vector rotate
	virtual void RecalculateState(float& game_time);

	//for heal collisions
	void TerminateCollision(GameObject& game_object);
	void TerminateCollision(MovebleObject& moveble_object);
};

class TankObject : public MovebleObject //++++++++++++++++++++++++++++++++++++
{
private:
	float speed_shot_, shot_distance_, time_to_next_shot_, time_freeze_shot_;

protected:
	virtual MovebleObject* Shot();
public:
	TankObject();
	TankObject(int id_object,
		sf::Vector2f coordinate_centre,
		sf::Vector2f offset_sprite_coordinate,
		string texture, int frame_count_x, int frame_count_y,
		int life_level, float speed, float freeze_time,
		float speed_shot, float shot_distance, float time_freeze_shot);

	bool CanCreateShot();
	MovebleObject* CreateShot(bool forcibly_shot = false);
	void RecalculateState(float& game_time) override; //+recalculate time_to_next_shot

	float GetSpeedShot();
	float GetShotDistance();
	float GetTimeToNextShot();
	float GetTimeFreezeShot();

	void SetSpeedShot(float speed_shot);
	void SetShotDistance(float shot_distance);
	void SetTimeToNextShot(float time_to_next_shot);
	void SetTimeFreezeShot(float time_freeze_shot);
};