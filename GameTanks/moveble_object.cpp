#include "objects.h"

MovebleObject::MovebleObject() : GameObject() {}

MovebleObject::MovebleObject(int const& id_object,
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	string const& texture, int const& frame_count_x, int const& frame_count_y,
	int const& life_level, float const& speed, float const& freeze_time)
	: GameObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y, life_level)
{
	SetSpeed(speed);
	SetFreezeTime(freeze_time);
}

//set object parameters
void MovebleObject::SetSpeed(float const& speed)
{ speed_ = speed; }

void MovebleObject::SetFreezeTime(float const& freeze_time)
{ freeze_time_ = freeze_time; }

void MovebleObject::SetDistance(float const& distance, bool const& add_to_previous)
{
	if (add_to_previous) { distance_ += distance; }
	else{ distance_ = distance; }
}

//get object parameters
float MovebleObject::GetSpeed() 
{ return speed_; }
float MovebleObject::GetDistance() 
{ return distance_; }
float MovebleObject::GetFreezeTime() 
{ return freeze_time_; }

void MovebleObject::MoveTo(int const& move_to_x, int const& move_to_y)
{
	//<-------------------------------------------------------------------
	//calculate and set vector;
	//calculate and set distance;	
}

//for recalculate position ((vector+speed+distance)*timer), vector rotate
void MovebleObject::RecalculateState(float const& game_time)
{
	//<-------------------------------------------------------------------
	
	//slow rotate vector;

	//calculate length move frame (number)
	//calculate coordinares offset by move
	//add offset to current position
	
}

//for heal collisions
void MovebleObject::TerminateCollision(GameObject const& game_object)
{
	//<-------------------------------------------------------------------
}
void MovebleObject::TerminateCollision(MovebleObject const& moveble_object)
{
	//<-------------------------------------------------------------------
}