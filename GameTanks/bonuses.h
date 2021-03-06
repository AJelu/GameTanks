#pragma once
#include <iostream>

//Class for add temp bonus to tanks (for players)

class Bonuses {
private:
	float bonus_duration_, //bunus time
		//Current stats (%):
		speed_move_, rotation_speed_,
		speed_shot_, shot_distance_, time_freeze_shot_,
		shot_life_, life_level_, max_life_level_;

	//Original parametrs:
	float o_bonus_duration_, //bunus time
		o_speed_move_, o_rotation_speed_,
		o_speed_shot_, o_shot_distance_, o_time_freeze_shot_;
	int o_shot_life_, o_life_level_, o_max_life_level_;

	//Function generate random stats:
	void GenerateSpeed();
	void GenerateRotation();
	void GenerateShotPower();
	void GenerateShotSpeed();
	void GenerateLife();

public:
	Bonuses();
	Bonuses(float bonus_duration);
	Bonuses(float bonus_duration,
		float speed_move, float rotatino_speed,
		float shot_life, float speed_shot, float shot_distance, float time_freeze_shot,
		float life_level, float max_life_level);

	float GetBonusDuration(float const& game_time);

	//Get new parameters:
	float GetSpeedMove();
	float GetRotationSpeed();

	float GetSpeedShot();
	float GetShotDistance();
	float GetTimeFreezeShot();
	int GetShotLife();

	int GetLifeLevel();
	int GetMaxLifeLevel();

	//Get original parameters:
	float GetOriginalSpeedMove();
	float GetOriginalRotationSpeed();

	float GetOriginalSpeedShot();
	float GetOriginalShotDistance();
	float GetOriginalTimeFreezeShot();
	int GetOriginalShotLife();

	int GetOriginalLifeLevel();
	int GetOriginalMaxLifeLevel();

	void SetOriginalSpeedMove(float const& o_speed_move);
	void SetOriginalRotationSpeed(float const& o_rotatino_speed);

	void SetOriginalSpeedShot(float const& o_speed_shot);
	void SetOriginalShotDistance(float const& o_shot_distance);
	void SetOriginalTimeFreezeShot(float const& o_time_freeze_shot);
	void SetOriginalShotLife(int const& o_shot_life);

	void SetOriginalLifeLevel(int const& o_life_level);
	void SetOriginalMaxLifeLevel(int const& o_max_life_level);
};