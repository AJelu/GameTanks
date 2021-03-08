#include "objects.h"

TankObject::TankObject() : MovebleObject() {
	SetSpeedShot(1000);
	SetShotDistance(1000);
	SetTimeFreezeShot(1000);
	SetTimeToNextShot(0);
}

TankObject::TankObject(int const& id_object,
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	std::string const& texture, int const& frame_count_x, int const& frame_count_y,
	int const& life_level, float const& speed, float const& freeze_time,
	float const& rotation_speed,
	float const& speed_shot, float const& shot_distance, 
	float const& time_freeze_shot)
	: MovebleObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y,
		life_level, speed, freeze_time, rotation_speed) {
	SetSpeedShot(speed_shot);
	SetShotDistance(shot_distance);
	SetTimeFreezeShot(time_freeze_shot);
	SetTimeToNextShot(0);
}

MovebleObject* TankObject::Shot() { return nullptr; }

bool TankObject::CanCreateShot() { return time_to_next_shot_ <= 0; }

//return null. no shot. overriding in daughter classes
MovebleObject* TankObject::CreateShot(bool const& forcibly_shot) { 
	if (time_to_next_shot_ <= 0 || forcibly_shot) {
		time_to_next_shot_ = time_freeze_shot_;
		MovebleObject* shot = Shot();
		if (shot != nullptr) {
			shot->SetSpeedMove(speed_shot_);
			shot->SetDistanceMove(shot_distance_);
			shot->SetRotationVector(this->GetVectorX(), this->GetVectorY());
			this->StartAudioAction("shot", false);
			return shot;
		}
	}
	return nullptr; 
}

//+recalculate time_to_next_shot 
void TankObject::RecalculateState(float const& game_time) {
	MovebleObject::RecalculateState(game_time);
	
	if (time_to_next_shot_ < 0.0f)		time_to_next_shot_ = 0.0f;
	else if (time_to_next_shot_ > 0.0f) time_to_next_shot_ -= game_time;
}

void TankObject::MoveUp() { SetDistanceMove(5); }

void TankObject::MoveDown() { SetDistanceMove(-5); }

void TankObject::MoveRight() { SetRotationDegree(5); }

void TankObject::MoveLeft() { SetRotationDegree(-5); }


float TankObject::GetSpeedShot() { return speed_shot_; }

float TankObject::GetShotDistance() { return shot_distance_; }

float TankObject::GetTimeToNextShot() { return time_to_next_shot_; }

float TankObject::GetTimeFreezeShot() { return time_freeze_shot_; }


void TankObject::SetSpeedShot(float const& speed_shot) { speed_shot_ = speed_shot; }

void TankObject::SetShotDistance(float const& shot_distance) { shot_distance_ = shot_distance; }

void TankObject::SetTimeToNextShot(float const& time_to_next_shot) { 
	time_to_next_shot_ = time_to_next_shot; 
}

void TankObject::SetTimeFreezeShot(float const& time_freeze_shot) { time_freeze_shot_ = time_freeze_shot; }
