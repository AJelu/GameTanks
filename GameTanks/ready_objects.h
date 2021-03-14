#pragma once

#include "objects.h"

class Bullet : public MovebleObject {
private:
	void PlayAnimateDie() override;
	void PlayAnimateLife() override;
	void PlayAnimateMovePlus() override;

public:
	Bullet(int const& id_object, GameObject* Parrent = nullptr);
};

class TypedTank abstract : public TankObject {
public:
	TypedTank(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture,
		int const& max_life_level,
		float const& speed, float const& freeze_time,
		float const& rotation_speed, sf::Vector2f const& point_create_shot_by_vector,
		int const& shot_life, float const& speed_shot, float const& 
		shot_distance, float const& time_freeze_shot, GameObject* Parrent);

	void PlayAnimateDie() override;
	void PlayAnimateLife() override;
	void PlayAnimateMovePlus() override;
	void PlayAnimateMoveMinus() override;
	void PlayAnimateRotate—lockwise() override;
	void PlayAnimateRotate—ounterclockwise() override;
};

class RedTank : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	RedTank(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
};

class Tank2 : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	Tank2(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
};

class Tank3 : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	Tank3(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
};

class Tank4 : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	Tank4(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
};

class Tank5 : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	Tank5(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
};

class Tank6 : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	Tank6(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
};