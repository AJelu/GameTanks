#include "objects.h"

MovebleObject::MovebleObject() : GameObject() 
{
	this->SetSpeedMove(50);
	this->SetFreezeTime(0);
	this->SetRotationSpeed(360);
	distance_ = 0;
	rotation_degree_ = 0;
}

MovebleObject::MovebleObject(int const& id_object,
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	string const& texture, int const& frame_count_x, int const& frame_count_y,
	int const& life_level, float const& speed, float const& freeze_time,
	float const& rotation_speed)
	: GameObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y, life_level)
{
	this->SetSpeedMove(speed);
	this->SetFreezeTime(freeze_time);
	this->SetRotationSpeed(rotation_speed);
	distance_ = 0;
	rotation_degree_ = 0;
}

//set object parameters
void MovebleObject::SetSpeedMove(float const& speed)
{ speed_ = speed; }

void MovebleObject::SetFreezeTime(float const& freeze_time)
{ freeze_time_ = freeze_time; }

void MovebleObject::SetDistanceMove(float const& distance, 
	bool const& add_to_previous)
{
	if (add_to_previous) { distance_ += distance; }
	else{ distance_ = distance; }
}

void MovebleObject::SetRotationDegree(float const& rotation_degree,
	bool const& add_to_previous)
{
	if (add_to_previous) { rotation_degree_ += rotation_degree; }
	else { rotation_degree_ = rotation_degree; }
}

void MovebleObject::SetRotationSpeed(float const& rotation_speed)
{ rotation_speed_ = rotation_speed; }

//get object parameters
float MovebleObject::GetSpeedMove() 
{ return speed_; }
float MovebleObject::GetDistanceMove() 
{ return distance_; }
float MovebleObject::GetFreezeTime() 
{ return freeze_time_; }

void MovebleObject::MoveTo(float const& move_to_x, float const& move_to_y)
{
	this->SetRotationVector(move_to_x, move_to_y);
	float temp_vector_x = move_to_x - GetVectorX();//create and set temp vector
	float temp_vector_y = move_to_y - GetVectorY();
	float length_vector =
		temp_vector_x * temp_vector_x
		+ temp_vector_y * temp_vector_y;
	if (length_vector != 0.0f) { length_vector = sqrtf(length_vector); }

	length_vector = sqrtf(length_vector);
	this->SetDistanceMove(length_vector);
}

//for recalculate position ((speed+distance)*timer), vector rotate
void MovebleObject::RecalculateState(float const& game_time)
{
	if (freeze_time_ > 0) {
		distance_ = rotation_degree_ = 0;
		freeze_time_ -= game_time;
	}

	//move by vector;
	float size;
	if (distance_ != 0) {
		size = (game_time / 1000/*1 sec*/) * speed_;

		if (distance_ < 0) {
			distance_ += size;
			if (distance_ > 0) {
				size -= distance_;
				distance_ = 0;
			}
			this->MoveByVector(-size);
		}
		else if (distance_ > 0) {
			distance_ -= size;
			if (distance_ < 0) {
				size += distance_;
				distance_ = 0;
			}
			this->MoveByVector(size);
		}
	}

	//rotate vector;
	if (rotation_degree_ != 0) {
		size = (game_time / 1000/*1 sec*/) * rotation_speed_;

		if (rotation_degree_ < 0) {
			rotation_degree_ += size;
			if (rotation_degree_ > 0) {
				size -= rotation_degree_;
				rotation_degree_ = 0;
			}
			this->VectorRotation(-size);
		}
		else if (rotation_degree_ > 0) {
			rotation_degree_ -= size;
			if (rotation_degree_ < 0) {
				size += rotation_degree_;
				rotation_degree_ = 0;
			}
			this->VectorRotation(size);
		}
	}
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