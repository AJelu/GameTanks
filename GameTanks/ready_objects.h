#pragma once

#include "objects.h"

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
		std::string const& texture,
		int const& max_life_level);
	void ActionDie() override;
	void ActionLife() override;
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
public:
	BlockGround(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class BlockGrass : public CommonGameObject {
public:
	BlockGrass(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class CactusTypeOne : public CommonGameObject {
public:
	CactusTypeOne(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class CactusTypeTwo : public CommonGameObject {
public:
	CactusTypeTwo(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class CactusTypeThree : public CommonGameObject {
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
public:
	TreeTypeOne(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeTwo : public CommonGameObject {
public:
	TreeTypeTwo(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeThree : public CommonGameObject {
public:
	TreeTypeThree(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeFour : public CommonGameObject {
public:
	TreeTypeFour(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeFive : public CommonGameObject {
public:
	TreeTypeFive(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeSix : public CommonGameObject {
public:
	TreeTypeSix(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeSeven : public CommonGameObject {
public:
	TreeTypeSeven(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeEight : public CommonGameObject {
public:
	TreeTypeEight(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class TreeTypeNine : public CommonGameObject {
public:
	TreeTypeNine(int const& id_object, float const& spawn_x, float const& spawn_y);
};

class Well : public CommonGameObject {
public:
	Well(int const& id_object, float const& spawn_x, float const& spawn_y);
};