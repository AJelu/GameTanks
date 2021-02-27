#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "Collisions.h"
#include "Actions.h"

using namespace std;
using namespace sf;

//this objects using in levels to create game experience: game menu, game levels

class BaseObject
{
private:
	int id_object; //for synchronize by lan

public:
	BaseObject(int id_object, int x, int y);	

	//get object parameters
	int GetIdObject();
	//set object parameters
	virtual void SetCoordinate(int x_coordinate, int y_coordinate);
	virtual ~BaseObject() = 0;
};

class AudioObject : BaseObject 
{
private:
	vector <string> audio_action_name_;
	vector <Sound*> sounds_file_;
	vector <SoundBuffer*> sounds_buffer_;
	vector <int> sounds_volume_;
public:
	void AddAudioAction(string audio_action, string audio_file, int volume);
	bool StartAudioAction(string audio_action, bool looped);
	bool StopAudioAction(string audio_action);
	~AudioObject() override;
};

class VisibleObject : AudioObject
{
private:
	bool need_redraw_image_; //using for redraw screen. if have changing - true
	
	int offset_sprite_coordinate_x_, offset_sprite_coordinate_y;

	//for animates
	int frame_size_x_, frame_size_y_;
	int tile_level_, frame_start_, frame_end_;
	bool looped_;
	float current_frame_;

	Texture Texture_object_;
	Sprite Sprite_object_;
protected:
	//calculate if this object is within the range of the rectangle
	void SetNeedRedrawImage();
public:
	VisibleObject(int id_object, 
		int x, int y,
		int offset_sprite_coordinate_x, int offset_sprite_coordinate_y,
		string texture, int frame_size_x, int frame_size_y);

	void StartPlayAnimate(int tile_level, int frame_start, int frame_end, bool looped);
	bool AnimateEnd();
	void ForAnimate(float& game_time); //counting current frame

	//get object parameters
	bool GetNeedRedrawImage(); //return true if need update image
	int GetCoordinateX();
	int GetCoordinateY();

	//set object parameters
	void SetCoordinate(int x_coordinate, int y_coordinate);
	void SetTexture(string texture, int frame_size_x, int frame_size_y);
	void SetOffsetSpriteCoordinate(int offset_sprite_coordinate_x, int offset_sprite_coordinate_y);

	bool Draw(sf::RenderWindow& window, View& Player_camera, bool plus_offset_camera = false);
};



class UiObject : VisibleObject
{
private:
	bool focus_on_this_, down_on_this_, up_on_this_;
	string text_;

	BaseAction* On_mouse_up_action_; /////////////////////////////////////

public:
	UiObject(int id_object,
		int x, int y,
		int offset_sprite_coordinate_x, int offset_sprite_coordinate_y,
		string texture, int frame_size_x, int frame_size_y,
		BaseAction* On_mouse_up_action);
	bool IsFocusOnThis(int x, int y);
	bool IsDownOnThis(int x, int y);
	bool IsUpOnThis(int x, int y);
	void AddInputText(string text);
	void SetText(string text);


	bool FocusOnThis();
	bool DownOnThis();
	bool UpOnThis();
	string GetText();

	~UiObject() override;
};

class Button : UiObject
{
public:

};

//others ui objects



class GameObject : VisibleObject
{
private:
	int life_level_;
	vector <RoundCollision> collisions_;

public:
	GameObject(int id_object, 
		int x, int y,
		int offset_sprite_coordinate_x, int offset_sprite_coordinate_y,
		string texture, int frame_size_x, int frame_size_y,
		int life_level);

	void SetLifeLevel();
	int GetLifeLevel();
	void AddCollision(RoundCollision& new_colision);
	float DistanceToCollision(GameObject& game_object);
};


class MovebleObject : GameObject
{
private:
	float vector_x_, vector_y_, speed_, distance_, freeze_time_;
	int rotation_degree_;

	void RecalculateVector();

public:
	MovebleObject(int id_object, 
		int x, int y,
		int offset_sprite_coordinate_x, int offset_sprite_coordinate_y,
		string texture, int frame_size_x, int frame_size_y,
		int life_level, float speed);

	//set object parameters
	void SetVector(float vector_x, float vector_y);
	void RotationVector(int rotation_degree);
	void SetSpeed(float speed);
	void SetFreezeTime(float freeze_time);
	void SetDistance(float distance, bool add_to_previous = false);

	//get object parameters
	float GetVectorX();
	float GetVectorY();
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

class TankObject : MovebleObject
{
private:
	float speed_shot_, shot_distance_, time_to_next_shot_, time_freeze_shot_;
public:
	TankObject(int id_object, 
		int x, int y,
		int offset_sprite_coordinate_x, int offset_sprite_coordinate_y,
		string texture, int frame_size_x, int frame_size_y,
		int life_level, float speed, float speed_shot, float shot_distance);

	virtual MovebleObject* CreateShot();
	void RecalculateState(float& game_time) override; //+recalculate time_to_next_shot

	float GetSpeedShot();
	float GetShotDistance();
	float GetTimeToNextShot();
	float GetTimeFreezeShot();

	void SetSpeedShot(float speed_shot);
	void SetShotDistance(float shot_distance);
	void SetTimeToNextShot(float time_to_next_shot);
	void GetTimeFreezeShot(float time_freeze_shot);
};