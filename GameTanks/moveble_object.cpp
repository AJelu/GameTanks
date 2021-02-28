#include "objects.h"

MovebleObject::MovebleObject() : GameObject() {}

MovebleObject::MovebleObject(int id_object,
	sf::Vector2f coordinate_centre,
	sf::Vector2f offset_sprite_coordinate,
	string texture, int frame_count_x, int frame_count_y,
	int life_level, float speed, float freeze_time)
	: GameObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y, life_level)
{
	SetSpeed(speed);
	SetFreezeTime(freeze_time);
}

//set object parameters
void MovebleObject::SetSpeed(float speed)
{ speed_ = speed; }

void MovebleObject::SetFreezeTime(float freeze_time)
{ freeze_time_ = freeze_time; }

void MovebleObject::SetDistance(float distance, bool add_to_previous)
{
	if (add_to_previous) { distance_ += distance; }
	else{ distance = distance_; }
}

//get object parameters
float MovebleObject::GetSpeed() 
{ return speed_; }
float MovebleObject::GetDistance() 
{ return distance_; }
float MovebleObject::GetFreezeTime() 
{ return freeze_time_; }

void MovebleObject::MoveTo(int move_to_x, int move_to_y)
{
	//<-------------------------------------------------------------------
	//calculate and set vector;
	//calculate and set distance;	
}

//for recalculate position ((vector+speed+distance)*timer), vector rotate
void MovebleObject::RecalculateState(float& game_time)
{
	//<-------------------------------------------------------------------
	
	//slow rotate vector;

	//calculate length move frame (number)
	//calculate coordinares offset by move
	//add offset to current position
	
}

//for heal collisions
void MovebleObject::TerminateCollision(GameObject& game_object)
{
	//<-------------------------------------------------------------------
}
void MovebleObject::TerminateCollision(MovebleObject& moveble_object)
{
	//<-------------------------------------------------------------------
}