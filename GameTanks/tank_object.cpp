#include "objects.h"
TankObject::TankObject() : MovebleObject()
{

}

TankObject::TankObject(int id_object,
	sf::Vector2f coordinate_centre,
	sf::Vector2f offset_sprite_coordinate,
	string texture, int frame_size_x, int frame_size_y,
	int life_level, float speed, float freeze_time,
	float speed_shot, float shot_distance, float time_freeze_shot)
	: MovebleObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_size_x, frame_size_y,
		life_level, speed, freeze_time)
{
	speed_shot_ = speed_shot;
	shot_distance_ = shot_distance;
	time_freeze_shot_ = time_freeze_shot;
	time_to_next_shot_ = 0;
}

//return null. no shot. overriding in daughter classes
//MovebleObject* TankObject::CreateShot() { return nullptr; }

void TankObject::RecalculateState(float& game_time) //+recalculate time_to_next_shot
{
	//MovebleObject::RecalculateState(game_time);
	//recalculate time_to_next_shot
}

float TankObject::GetSpeedShot() { return speed_shot_; }
float TankObject::GetShotDistance() { return shot_distance_; }
float TankObject::GetTimeToNextShot() { return time_to_next_shot_; }
float TankObject::GetTimeFreezeShot() { return time_freeze_shot_; }

void TankObject::SetSpeedShot(float speed_shot)
{ speed_shot_ = speed_shot; }

void TankObject::SetShotDistance(float shot_distance)
{ shot_distance_ = shot_distance; }

void TankObject::SetTimeToNextShot(float time_to_next_shot)
{ time_to_next_shot_ = time_to_next_shot; }

void TankObject::SetTimeFreezeShot(float time_freeze_shot)
{ time_freeze_shot_ = time_freeze_shot; }

TankObject::~TankObject()
{
}
