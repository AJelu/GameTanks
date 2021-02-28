#include "objects.h"

MovebleObject::MovebleObject() : GameObject() {}

MovebleObject::MovebleObject(int id_object,
	sf::Vector2f coordinate_centre,
	sf::Vector2f offset_sprite_coordinate,
	string texture, int frame_size_x, int frame_size_y,
	int life_level, float speed, float freeze_time)
	: GameObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_size_x, frame_size_y, life_level)
{
	SetSpeed(speed);
	SetFreezeTime(freeze_time);
}

void MovebleObject::RecalculateVector()
{

}

//set object parameters
void MovebleObject::SetVector(float vector_x, float vector_y)
{

}

void MovebleObject::RotationVector(int rotation_degree)
{

}

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
float MovebleObject::GetVectorX() { return vector_x_; }
float MovebleObject::GetVectorY() { return vector_x_; }
float MovebleObject::GetSpeed() { return speed_; }
float MovebleObject::GetDistance() { return distance_; }
float MovebleObject::GetFreezeTime() { return freeze_time_; }

void MovebleObject::MoveTo(int move_to_x, int move_to_y)
{
	
	//calculate and set vector;
	//set size vector is 1;
	//calculate and set distance;
	
}

//for recalculate position ((vector+speed+distance)*timer), vector rotate
void MovebleObject::RecalculateState(float& game_time)
{
	
	//check if need vector rotation and rotate vector;
	//calculate length move (number)
	//calculate coordinares offset
	//add offset to current position
	
}

//for heal collisions
void MovebleObject::TerminateCollision(GameObject& game_object)
{

}
void MovebleObject::TerminateCollision(MovebleObject& moveble_object)
{

}