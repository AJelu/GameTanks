#include "objects.h"

TankObject::TankObject() : MovebleObject() {
	this->SetLifeShot(1);
	this->SetPointCreateShot(sf::Vector2f(0, 0));
	this->SetSpeedShot(1000);
	this->SetShotDistance(100);
	this->SetTimeFreezeShot(1000);
	this->SetTimeToNextShot(0);
}

TankObject::TankObject(int const& id_object,
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	std::string const& texture, int const& frame_count_x, int const& frame_count_y,
	int const& max_life_level, float const& speed, float const& freeze_time,
	float const& rotation_speed, sf::Vector2f const& point_create_shot_by_vector,
	int const& shot_life, float const& speed_shot, float const& shot_distance,
	float const& time_freeze_shot, GameObject* Parrent)
	: MovebleObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y,
		max_life_level, speed, freeze_time, rotation_speed, Parrent) {
	this->SetLifeShot(shot_life);
	this->SetPointCreateShot(point_create_shot_by_vector);
	this->SetSpeedShot(speed_shot);
	this->SetShotDistance(shot_distance);
	this->SetTimeFreezeShot(time_freeze_shot);
	this->SetTimeToNextShot(0);
}

void TankObject::DeleteBonusFromObject(Bonuses * bonus) {
	this->SetSpeedMove(		bonus->GetOriginalSpeedMove());
	this->SetRotationSpeed(	bonus->GetOriginalRotationSpeed());
	this->SetSpeedShot(		bonus->GetOriginalSpeedShot());
	this->SetShotDistance(	bonus->GetOriginalShotDistance());
	this->SetTimeFreezeShot(bonus->GetOriginalTimeFreezeShot());
	this->SetLifeShot(		bonus->GetOriginalShotLife());
	this->SetNeedSynchByLan(true);
}

void TankObject::AddBonusToObject(Bonuses* bonus) {
	if (Bonus_ != nullptr) {
		this->DeleteBonusFromObject(Bonus_);
		delete Bonus_;
		Bonus_ = nullptr;
	}
	
	//Save original parameters
	bonus->SetOriginalSpeedMove(		this->GetSpeedMove());
	bonus->SetOriginalRotationSpeed(	this->GetRotationSpeed());
	bonus->SetOriginalSpeedShot(		this->GetSpeedShot());
	bonus->SetOriginalShotDistance(		this->GetShotDistance());
	bonus->SetOriginalTimeFreezeShot(	this->GetTimeFreezeShot());
	bonus->SetOriginalShotLife(			this->GetLifeShot());
	bonus->SetOriginalLifeLevel(		this->GetLifeLevel());
	bonus->SetOriginalMaxLifeLevel(		this->GetMaxLifeLevel());

	//Apply new parameters
	this->SetSpeedMove(		bonus->GetSpeedMove());
	this->SetRotationSpeed(	bonus->GetRotationSpeed());
	this->SetSpeedShot(		bonus->GetSpeedShot());
	this->SetShotDistance(	bonus->GetShotDistance());
	this->SetTimeFreezeShot(bonus->GetTimeFreezeShot());
	this->SetLifeShot(		bonus->GetShotLife());
	this->SetMaxLifeLevel(	bonus->GetMaxLifeLevel());
	this->SetLifeLevel(		bonus->GetLifeLevel());
	Bonus_ = bonus;
	this->SetNeedSynchByLan(true);
}

void TankObject::AddBonus(Bonuses* bonus) {
	if (bonus != nullptr) this->AddBonusToObject(bonus);
}

Bonuses* TankObject::GetBonus() { return Bonus_; }

MovebleObject* TankObject::Shot() { return nullptr; }

bool TankObject::CanCreateShot() { return time_to_next_shot_ <= 0; }

//Always return null if shot() not overriding in daughter classes
MovebleObject* TankObject::CreateShot(bool const& forcibly_shot) { 
	if ((time_to_next_shot_ <= 0 && this->GetFreezeTime() <= 0) || forcibly_shot) {
		time_to_next_shot_ = time_freeze_shot_;
		MovebleObject* shot = Shot();
		if (shot != nullptr) {
			shot->SetSpeedMove(speed_shot_);
			shot->SetDistanceMove(shot_distance_);
			shot->SetRotationVector(this->GetVectorX(), this->GetVectorY());
			sf::Vector2f temp_position_correcrtor
				= this->ChangeVectorByDirection(this->GetPointCreateShot());
			temp_position_correcrtor.y *= -1;
			shot->SetCoordinate(this->GetCoordinateCentre() + temp_position_correcrtor);
			shot->SetLifeLevel(this->GetLifeShot());
			return shot;
		}
	}
	return nullptr; 
}

// +Recalculate time_to_next_shot 
void TankObject::RecalculateState(float const& game_time) {
		MovebleObject::RecalculateState(game_time);
	if (time_to_next_shot_ < 0.0f)		time_to_next_shot_ = 0.0f;
	else if (time_to_next_shot_ > 0.0f) time_to_next_shot_ -= game_time;

	if (Bonus_ != nullptr && Bonus_->GetBonusDuration(game_time) <= 0) {
		this->DeleteBonusFromObject(Bonus_);
		delete Bonus_;
		Bonus_ = nullptr;
	}
}

void TankObject::MoveUp(float const& value) { SetDistanceMove(value); }

void TankObject::MoveDown(float const& value) { SetDistanceMove(-value); }

void TankObject::MoveRight(float const& value) { SetRotationDegree(value); }

void TankObject::MoveLeft(float const& value) { SetRotationDegree(-value); }

sf::Vector2f TankObject::GetPointCreateShot() { return Point_create_shot_; }

float TankObject::GetSpeedShot() { return speed_shot_; }

int TankObject::GetLifeShot() { return shot_life_; }

float TankObject::GetShotDistance() { return shot_distance_; }

float TankObject::GetTimeToNextShot() { return time_to_next_shot_; }

float TankObject::GetTimeFreezeShot() { return time_freeze_shot_; }

void TankObject::SetPointCreateShot(sf::Vector2f const& point_create_shot) {
	Point_create_shot_ = point_create_shot;
}

void TankObject::SetSpeedShot(float const& speed_shot) { speed_shot_ = speed_shot; }

void TankObject::SetLifeShot(int const& shot_life) { shot_life_ = shot_life; }

void TankObject::SetShotDistance(float const& shot_distance) { 
	shot_distance_ = shot_distance; 
}

void TankObject::SetTimeToNextShot(float const& time_to_next_shot) { 
	time_to_next_shot_ = time_to_next_shot; 
}

void TankObject::SetTimeFreezeShot(float const& time_freeze_shot) { 
	time_freeze_shot_ = time_freeze_shot; 
}

std::string TankObject::ClassName() { return "TankObject"; }

bool TankObject::CreatePacket(sf::Packet& Packet) {
	bool result = MovebleObject::CreatePacket(Packet);
	Packet << speed_shot_ << shot_distance_;
	Packet << time_to_next_shot_ << time_freeze_shot_;
	Packet << shot_life_;
	return result;
}

bool TankObject::SetDataFromPacket(sf::Packet& Packet) {
	if (MovebleObject::SetDataFromPacket(Packet)) {
		Packet >> speed_shot_ >> shot_distance_;
		Packet >> time_to_next_shot_ >> time_freeze_shot_;
		Packet >> shot_life_;
		return true;
	}
	return false;
}
