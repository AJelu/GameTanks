#pragma once

#include "objects.h"

//TEST:
static sf::Sound tank_move_, tank_rotate_, tank_dead_;
static sf::SoundBuffer buff_tank_move_, buff_tank_rotate_, buff_tank_dead_;

static sf::Sound bullet_shot_, bullet_explosion_;
static sf::SoundBuffer buff_bullet_shot_, buff_bullet_explosion_;
//+++

//move objects:
class Bullet : public MovebleObject {
private:
	void ActionDie() override;
	void ActionLife() override;
	void ActionMoving(float const& distance) override;

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
		int const& shot_life, float const& speed_shot, float const& shot_distance, 
		float const& time_freeze_shot, GameObject* Parrent);

	void ActionDie() override;
	void ActionLife() override;
	void ActionStartMove() override;
	void ActionMoving(float const& distance) override;
	void ActionEndMove() override;
	void ActionStartRotate() override;
	void ActionRotating(float const& rotation_degree) override;
	void ActionEndRotate() override;
};

class RedTank : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	RedTank(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
};

class TankBrown : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	TankBrown(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
};

class TankWhite : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	TankWhite(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
};

class TankBlack : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	TankBlack(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
};

class TankYellow : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	TankYellow(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
};

class TankGreen : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	TankGreen(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
};


//ui objects:
class Button : public UiObject {
public:
	Button(sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate);

	void ActionEnter() override;
	void ActionLeave() override;
	void ActionClickDown() override;
	void ActionClickUp() override;
};


//game objects:
class CommonGameObject abstract : public GameObject {
public:
	CommonGameObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture, int const& frame_count_x, int const& frame_count_y,
		int const& max_life_level);
};

class BarellBrown : public CommonGameObject {
public:
	BarellBrown(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class BarellBroken : public CommonGameObject {
public:
	BarellBroken(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class BarellGreen : public CommonGameObject {
public:
	BarellGreen(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class BlockGround : public CommonGameObject {
private:
	void ActionDie() override;

public:
	BlockGround(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class BlockGrass : public CommonGameObject {
private:
	void ActionDie() override;

public:
	BlockGrass(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class CactusTypeOne : public CommonGameObject {
private:
	void ActionDie() override;

public:
	CactusTypeOne(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class CactusTypeTwo : public CommonGameObject {
private:
	void ActionDie() override;

public:
	CactusTypeTwo(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class CactusTypeThree : public CommonGameObject {
private:
	void ActionDie() override;

public:
	CactusTypeThree(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class Log : public CommonGameObject {
public:
	Log(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class Star : public CommonGameObject {
public:
	Star(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class Stump : public CommonGameObject {
public:
	Stump(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeOne : public CommonGameObject {
private:
	void ActionDie() override;

public:
	TreeTypeOne(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeTwo : public CommonGameObject {
private:
	void ActionDie() override;

public:
	TreeTypeTwo(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeThree : public CommonGameObject {
private:
	void ActionDie() override;

public:
	TreeTypeThree(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeFour : public CommonGameObject {
private:
	void ActionDie() override;

public:
	TreeTypeFour(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeFive : public CommonGameObject {
private:
	void ActionDie() override;

public:
	TreeTypeFive(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeSix : public CommonGameObject {
private:
	void ActionDie() override;

public:
	TreeTypeSix(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeSeven : public CommonGameObject {
private:
	void ActionDie() override;

public:
	TreeTypeSeven(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeEight : public CommonGameObject {
private:
	void ActionDie() override;

public:
	TreeTypeEight(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeNine : public CommonGameObject {
private:
	void ActionDie() override;

public:
	TreeTypeNine(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class Well : public CommonGameObject {
private:
	void ActionDie() override;

public:
	Well(int const& id_object, float const& spawn_x, float const& spawn_y);
};