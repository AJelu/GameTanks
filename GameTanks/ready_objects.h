#pragma once

#include "objects.h"

//Move objects:
class Bullet : public MovebleObject {
private:
	void ActionDie() override;
	void ActionLife() override;
	void ActionMoving(float const& distance) override;

public:
	Bullet(int const& id_object, GameObject* Parrent = nullptr);
	std::string ClassName() override;
};

class DoubleBullet : public MovebleObject {
private:
	void ActionDie() override;
	void ActionLife() override;
	void ActionMoving(float const& distance) override;

public:
	DoubleBullet(int const& id_object, GameObject* Parrent = nullptr);
	std::string ClassName() override;
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
	std::string ClassName() override;
};

class TankBrown : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	TankBrown(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
	std::string ClassName() override;
};

class TankWhite : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	TankWhite(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
	std::string ClassName() override;
};

class TankBlack : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	TankBlack(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
	std::string ClassName() override;
};

class TankYellow : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	TankYellow(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
	std::string ClassName() override;
};

class TankGreen : public TypedTank {
protected:
	MovebleObject* Shot() override;

public:
	TankGreen(int const& id_object, float const& spawn_x, float const& spawn_y,
		GameObject* Parrent = nullptr);
	std::string ClassName() override;
};


//UI objects:
class Button : public UiObject {
public:
	Button(sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate);

	void ActionEnter() override;
	void ActionLeave() override;
	void ActionClickDown() override;
	void ActionClickUp() override;
};

class Loading : public UiObject {
public:
	Loading(sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate);
};

class PlayersTextBackground : public UiObject {
public:
	PlayersTextBackground(sf::Vector2f const& coordinate_centre);
};

class TextLine : public UiObject {
private:
	std::vector<UiObject*> Lines_;

	int one_line_text_size_,
		line_step_px_,
		one_line_ui_size_px_,
		width_;
public:
	TextLine(sf::Vector2f const& coordinate_centre, int const& width,
		int const& line_count, 
		int const& one_line_text_size, 
		int const& one_line_ui_size_px, int const& line_step_px);

	void TextAlign(float const& align);

	void ChangeCounLine(int const& line_count);
	void SetTextLine(std::string str, int const& line_number);
	std::string GetTextLine(int const& line_number);
	void Draw(sf::RenderWindow& window) override;

	~TextLine() override;
};

class ProgressLine : public UiObject {
private:
	UiObject *Fon_, *Progress_, *Border_;
	sf::Vector2f Scale_;

public:
	ProgressLine(sf::Vector2f const& coordinate_centre);
	void SetProgress(float const& progress);
	void Draw(sf::RenderWindow& window) override;
	~ProgressLine() override;
};

class Title : public UiObject {
public:
	Title(sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate);

	void ActionEnter() override;
	void ActionLeave() override;
};

//Game objects:
class CommonGameObject abstract : public GameObject {
public:
	CommonGameObject(int const& id_object,
		sf::Vector2f const& coordinate_centre,
		sf::Vector2f const& offset_sprite_coordinate,
		std::string const& texture,
		int const& max_life_level);
	void ActionDie() override;
	void ActionLife() override;
	void ActionChangeLifeLevel(int const& life_level) override;
};

class BarellBrown : public CommonGameObject {
public:
	BarellBrown(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class BarellBroken : public CommonGameObject {
public:
	BarellBroken(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class BarellGreen : public CommonGameObject {
public:
	BarellGreen(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class BlockGround : public CommonGameObject {
public:
	BlockGround(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class BlockGrass : public CommonGameObject {
public:
	BlockGrass(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class CactusTypeOne : public CommonGameObject {
public:
	CactusTypeOne(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class CactusTypeTwo : public CommonGameObject {
public:
	CactusTypeTwo(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class CactusTypeThree : public CommonGameObject {
public:
	CactusTypeThree(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class Log : public CommonGameObject {
public:
	Log(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class Star : public CommonGameObject {
public:
	Star(int const& id_object, float const& spawn_x, float const& spawn_y);
	void ActionLife() override;
	std::string ClassName() override;
};

class Stump : public CommonGameObject {
public:
	Stump(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class TreeTypeOne : public CommonGameObject {
public:
	TreeTypeOne(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class TreeTypeTwo : public CommonGameObject {
public:
	TreeTypeTwo(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class TreeTypeThree : public CommonGameObject {
public:
	TreeTypeThree(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class TreeTypeFour : public CommonGameObject {
public:
	TreeTypeFour(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class TreeTypeFive : public CommonGameObject {
public:
	TreeTypeFive(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class TreeTypeSix : public CommonGameObject {
public:
	TreeTypeSix(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class TreeTypeSeven : public CommonGameObject {
public:
	TreeTypeSeven(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class TreeTypeEight : public CommonGameObject {
public:
	TreeTypeEight(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class TreeTypeNine : public CommonGameObject {
public:
	TreeTypeNine(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};

class Well : public CommonGameObject {
public:
	Well(int const& id_object, float const& spawn_x, float const& spawn_y);
	std::string ClassName() override;
};