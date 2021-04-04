#include "objects.h"

MovebleObject::MovebleObject() : GameObject() {
	this->SetSpeedMove(50);
	this->SetFreezeTime(0);
	this->SetRotationSpeed(360);
	distance_ = 0;
	rotation_degree_ = 0;
}

MovebleObject::MovebleObject(int const& id_object,
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	std::string const& texture, int const& frame_count_x, int const& frame_count_y,
	int const& max_life_level, float const& speed, float const& freeze_time,
	float const& rotation_speed, GameObject* Parrent)
	: GameObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y, max_life_level, Parrent) {
	this->SetSpeedMove(speed);
	this->SetFreezeTime(freeze_time);
	this->SetRotationSpeed(rotation_speed);
	distance_ = 0;
	rotation_degree_ = 0;
}

//set object parameters
void MovebleObject::SetSpeedMove(float const& speed) { 
	speed_ = speed;
	this->SetNeedSynchByLan(true);
}

void MovebleObject::SetFreezeTime(float const& freeze_time) { 
	freeze_time_ = freeze_time;
	this->SetNeedSynchByLan(true);
}

void MovebleObject::SetDistanceMove(float const& distance, bool const& add_to_previous) {
	if (add_to_previous) distance_ += distance;
	else distance_ = distance;
	this->SetNeedSynchByLan(true);
}

void MovebleObject::SetRotationDegree(float const& rotation_degree, bool const& add_to_previous) {
	if (add_to_previous) rotation_degree_ += rotation_degree;
	else rotation_degree_ = rotation_degree;
	this->SetNeedSynchByLan(true);
}

void MovebleObject::SetRotationSpeed(float const& rotation_speed) { 
	rotation_speed_ = rotation_speed;
	this->SetNeedSynchByLan(true);
}

//get object parameters
float MovebleObject::GetSpeedMove() { return speed_; }

float MovebleObject::GetDistanceMove() { return distance_; }

float MovebleObject::GetFreezeTime() { return freeze_time_; }

float MovebleObject::GetRotationDegree() { return rotation_degree_; }

float MovebleObject::GetRotationSpeed() { return rotation_speed_; }

void MovebleObject::MoveTo(float const& move_to_x, float const& move_to_y) {
	this->SetRotationVector(move_to_x, move_to_y);
	float length_vector = powf(move_to_x - GetVectorX(), 2) + powf(move_to_y - GetVectorY(), 2);
	if (length_vector != 0.0f) length_vector = sqrtf(length_vector);
	this->SetDistanceMove(length_vector);
}

//for recalculate position ((speed+distance)*timer), vector rotate
void MovebleObject::RecalculateState(float const& game_time) {
	GameObject::RecalculateState(game_time);

	if (freeze_time_ > 0 || this->GetLifeLevel() <= 0) {
		this->SetDistanceMove(0);
		this->SetRotationDegree(0);
		if (this->GetLifeLevel() <= 0)	freeze_time_ = 1;
		else							freeze_time_ -= game_time;
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
			this->ActionMoving(-size);
		}
		else if (distance_ > 0) {
			distance_ -= size;
			if (distance_ < 0) {
				size += distance_;
				distance_ = 0;
			}
			this->MoveByVector(size);
			this->ActionMoving(size);
		}
		if (!previously_moveed_) {
			this->ActionStartMove();
			previously_moveed_ = true;
		}
	}
	else if (previously_moveed_) {
		this->ActionEndMove();
		previously_moveed_ = false;
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
			this->ActionRotating(-size);
		}
		else if (rotation_degree_ > 0) {
			rotation_degree_ -= size;
			if (rotation_degree_ < 0) {
				size += rotation_degree_;
				rotation_degree_ = 0;
			}
			this->VectorRotation(size); 
			this->ActionRotating(size);
		}
		if (!previously_rotated_) {
			this->ActionStartRotate();
			previously_rotated_ = true;
		}
	}
	else if (previously_rotated_) {
		this->ActionEndRotate();
		previously_rotated_ = false;
	}
}

std::string MovebleObject::ClassName() { return "MovebleObject"; }

bool MovebleObject::CreatePacket(sf::Packet& Packet) {
	bool result = GameObject::CreatePacket(Packet);
	Packet << speed_ << distance_ << freeze_time_;
	Packet << rotation_speed_ << rotation_degree_;
	return result;
}

bool MovebleObject::SetDataFromPacket(sf::Packet& Packet) {
	if (GameObject::SetDataFromPacket(Packet)) {
		Packet >> speed_ >> distance_ >> freeze_time_;
		Packet >> rotation_speed_ >> rotation_degree_;
		return true;
	}
	return false;
}

void MovebleObject::ActionStartMove() {}
void MovebleObject::ActionMoving(float const& distance) {}
void MovebleObject::ActionEndMove() {}
void MovebleObject::ActionStartRotate() {}
void MovebleObject::ActionRotating(float const& rotation_degree) {}
void MovebleObject::ActionEndRotate() {}
