#include "bonuses.h"
#include "settings.h"

void Bonuses::GenerateSpeed() { //Speed +20-50% / Rotation -20-50%
	speed_move_ = (rand() % 3 + 2) * 0.1f;
	rotation_speed_ = -speed_move_;
}

void Bonuses::GenerateRotation() { //Rotation +20-50% / Speed -20-50%
	rotation_speed_ = (rand() % 3 + 2) * 0.1f;
	speed_move_ = -rotation_speed_;
}

void Bonuses::GenerateShotPower() { //Damage +50-100% / Range -25-50% / Recharge -10%
	shot_life_ = (rand() % 10 + 5) * 0.1f;
	shot_distance_ = shot_life_ / 2;
	time_freeze_shot_ = 0.1f;
}

void Bonuses::GenerateShotSpeed() { //Range +20-50% / Recharge +10% / Damage -20-50%
	shot_distance_ = (rand() % 3 + 2) * 0.1f;
	time_freeze_shot_ = -0.1f;
	shot_life_ = -shot_distance_;
}

void Bonuses::GenerateLife() { //HP Regen +200% / Bonus HP +2
	life_level_ = 2;
	max_life_level_ = 0.02f;
}

Bonuses::Bonuses() {
	bonus_duration_ = float((TIME_DURATION_BONUS / 10) + (rand() % TIME_DURATION_BONUS));
	
	speed_move_			= 0.00;
	rotation_speed_		= 0.00;
	speed_shot_			= 0.00;
	shot_distance_		= 0.00;
	time_freeze_shot_	= 0.00;
	shot_life_			= 0.00;
	life_level_			= 0.00;
	max_life_level_		= 0.00;

	switch (rand() % 4) {
		case 0: this->GenerateSpeed();
			break;
		case 1: this->GenerateRotation();
			break;
		case 2: this->GenerateShotPower();
			break;
		case 3: this->GenerateShotSpeed();
			break;
	}
	this->GenerateLife();
}

Bonuses::Bonuses(float bonus_duration) {
	bonus_duration_		= bonus_duration;

	speed_move_			= 0.00;
	rotation_speed_		= 0.00;
	speed_shot_			= 0.00;
	shot_distance_		= 0.00;
	time_freeze_shot_	= 0.00;
	shot_life_			= 0.00;
	life_level_			= 0.00;
	max_life_level_		= 0.00;

	switch (rand() % 4) {
		case 0: this->GenerateSpeed();
			break;
		case 1: this->GenerateRotation();
			break;
		case 2: this->GenerateShotPower();
			break;
		case 3: this->GenerateShotSpeed();
			break;
	}
	this->GenerateLife();
}

Bonuses::Bonuses(float bonus_duration, 
		float speed_move, float rotatino_speed, 
		float shot_life, float speed_shot, float shot_distance, float time_freeze_shot,
		float life_level, float max_life_level) {
	bonus_duration_		= bonus_duration; 
	speed_move_			= speed_move;
	rotation_speed_		= rotatino_speed;
	speed_shot_			= speed_shot;
	shot_distance_		= shot_distance;
	time_freeze_shot_	= time_freeze_shot;
	shot_life_			= shot_life;
	life_level_			= life_level;
	max_life_level_		= max_life_level;
}

float Bonuses::GetBonusDuration(float const& game_time) {
	bonus_duration_ -= game_time;
	return bonus_duration_;
}

float Bonuses::GetSpeedMove() { 
	if (o_speed_move_ + o_speed_move_ * speed_move_ < 0) return 0.01f;
	return o_speed_move_ + o_speed_move_ * speed_move_; 
}

float Bonuses::GetRotationSpeed() {
	if (o_rotation_speed_ + o_rotation_speed_ * rotation_speed_ < 0) return 0.01f;
	return o_rotation_speed_ + o_rotation_speed_ * rotation_speed_; 
}

float Bonuses::GetSpeedShot() { 
	if (o_speed_shot_ + o_speed_shot_ * speed_shot_ < 0) return 0.01f;
	return o_speed_shot_ + o_speed_shot_ * speed_shot_; 
}

float Bonuses::GetShotDistance() {
	if (o_shot_distance_ + o_shot_distance_ * shot_distance_ < 0) return 1.0f;
	return o_shot_distance_ + o_shot_distance_ * shot_distance_; 
}

float Bonuses::GetTimeFreezeShot() {
	if ((o_time_freeze_shot_ + o_time_freeze_shot_ * time_freeze_shot_) < 0) 
		return 0.0f;
	return o_time_freeze_shot_ + o_time_freeze_shot_ * time_freeze_shot_; 
}

int Bonuses::GetShotLife() { 
	if (int(o_shot_life_ + o_shot_life_ * shot_life_) <= 0) return 1;
	return int(o_shot_life_ + o_shot_life_ * shot_life_); 
}

int Bonuses::GetLifeLevel() {
	if (int(o_life_level_ + o_life_level_ * life_level_) < 0) return 0;
	return int(o_life_level_ + o_life_level_ * life_level_); 
}

int Bonuses::GetMaxLifeLevel() {
	if (int(o_max_life_level_ + o_max_life_level_ * max_life_level_) <= 0) return 1;
	return int(o_max_life_level_ + o_max_life_level_ * max_life_level_); 
}

float Bonuses::GetOriginalSpeedMove() { return o_speed_move_; }

float Bonuses::GetOriginalRotationSpeed() { return o_rotation_speed_; }

float Bonuses::GetOriginalSpeedShot() { return o_speed_shot_; }

float Bonuses::GetOriginalShotDistance() { return o_shot_distance_; }

float Bonuses::GetOriginalTimeFreezeShot() { return o_time_freeze_shot_; }

int Bonuses::GetOriginalShotLife() { return o_shot_life_; }

int Bonuses::GetOriginalLifeLevel() { return o_life_level_; }

int Bonuses::GetOriginalMaxLifeLevel() { return o_max_life_level_; }

void Bonuses::SetOriginalSpeedMove(float const& o_speed_move) {
	o_speed_move_ = o_speed_move; }

void Bonuses::SetOriginalRotationSpeed(float const& o_rotatino_speed) {
	o_rotation_speed_ = o_rotatino_speed; }

void Bonuses::SetOriginalSpeedShot(float const& o_speed_shot) {
	o_speed_shot_ = o_speed_shot; }

void Bonuses::SetOriginalShotDistance(float const& o_shot_distance) {
	o_shot_distance_ = o_shot_distance; }

void Bonuses::SetOriginalTimeFreezeShot(float const& o_time_freeze_shot) {
	o_time_freeze_shot_ = o_time_freeze_shot; }

void Bonuses::SetOriginalShotLife(int const& o_shot_life) {
	o_shot_life_ = o_shot_life; }

void Bonuses::SetOriginalLifeLevel(int const& o_life_level) {
	o_life_level_ = o_life_level; }

void Bonuses::SetOriginalMaxLifeLevel(int const& o_max_life_level) {
	o_max_life_level_ = o_max_life_level; }