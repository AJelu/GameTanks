#include "ready_objects.h"

void Bullet::ActionDie() {
	this->ClearAnimarionList(true);
	this->StartPlayAnimation(1, 1, 9, 40); 
	this->StartAudioAction("Bullet_explosion");
}

void Bullet::ActionLife() {
	this->ClearAnimarionList(true);
	this->ActionMoving(0);
	this->StartAudioAction("Bullet_shot");
}

void Bullet::ActionMoving(float const& distance) { 
	this->StartPlayAnimation(2, 1, 8, 20); 
}

Bullet::Bullet(int const& id_object, GameObject* Parrent) : MovebleObject(
	id_object,
	sf::Vector2f(0, 0), //coordinate centr
	sf::Vector2f(96, 96), //offset
	"Data/Bullet/Boom_3.png", //texture
	9, 3,	//frame count
	1000000,//max life level
	500,	//speed move
	0,		//freeze time
	100,	//rotation speed
	Parrent) {
	this->AddAudioAction("Bullet_shot", "Data/Audio/explosion/bullet_shot.ogg", 50);
	this->AddAudioAction("Bullet_explosion", "Data/Audio/explosion/bullet_explosion.ogg");
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->ActionLife();
}

TypedTank::TypedTank(int const& id_object,
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	std::string const& texture,
	int const& max_life_level,
	float const& speed, float const& freeze_time,
	float const& rotation_speed, sf::Vector2f const& point_create_shot_by_vector,
	int const& shot_life, float const& speed_shot, float const& shot_distance,
	float const& time_freeze_shot,
	GameObject* Parrent) : TankObject(id_object, coordinate_centre,
		offset_sprite_coordinate, texture,
		12, 4, max_life_level,
		speed, freeze_time, rotation_speed, point_create_shot_by_vector,
		shot_life, speed_shot, shot_distance, time_freeze_shot, Parrent){ 

	this->AddAudioAction("TypedTank_move", "Data/Audio/move/tank_move.ogg", 50);
	this->AddAudioAction("TypedTank_rotate", "Data/Audio/move/tank_move_rotation.ogg", 50);
	this->AddAudioAction("TypedTank_dead", "Data/Audio/explosion/tank_dead.ogg");
	this->AddAudioAction("collision", "Data/Audio/collision/collision_tank.ogg", 40);
}

void TypedTank::ActionDie() {
	this->ClearAnimarionList();
	this->StartPlayAnimation(2, 1, 12, 70);
	this->StartAudioAction("TypedTank_dead");
}

void TypedTank::ActionLife() {
	this->ClearAnimarionList();
	this->StartPlayAnimation(1, 12, 1, 70); 
}

void TypedTank::ActionStartMove() {
	this->StartAudioAction("TypedTank_move", true);
}

void TypedTank::ActionMoving(float const& distance) {
	if (distance > 0)
		this->StartPlayAnimation(3, 1, 12, 40); 
	else if (distance < 0)
		this->StartPlayAnimation(3, 12, 1, 40);
}

void TypedTank::ActionEndMove() {
	this->StopAudioAction("TypedTank_move");
}

void TypedTank::ActionStartRotate() {
	this->StartAudioAction("TypedTank_rotate", true);
}

void TypedTank::ActionRotating(float const& distance) {
	if (distance > 0)
		this->StartPlayAnimation(4, 1, 6, 50);
	else if (distance < 0)
		this->StartPlayAnimation(4, 6, 1, 50);
}

void TypedTank::ActionEndRotate() {
	this->StopAudioAction("TypedTank_rotate");
}

RedTank::RedTank(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y), //coordinate centr
		sf::Vector2f(60, 158), //offset
		"Data/Unit/Tank1.png", //texture
		10,		//max life level
		200,	//speed move
		0,		//freeze time
		100,	//rotation speed
		sf::Vector2f(-1,150),	//create point shot
		1,		//shot life
		300,	//speed shot
		400,	//shot distance
		500,	//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
	this->SetBasePoint(200);
}

MovebleObject* RedTank::Shot() { return new Bullet(1, this); }


TankBrown::TankBrown(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y), //coordinate centr
		sf::Vector2f(60, 137), //offset
		"Data/Unit/Tank2.png", //texture
		5,		//max life level
		200,	//speed move
		0,		//freeze time
		100,	//rotation speed
		sf::Vector2f(-6, 129),	//create point shot
		1,		//shot life
		300,	//speed shot
		400,	//shot distance
		500,	//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
}

MovebleObject* TankBrown::Shot() { return new Bullet(1, this); }


TankWhite::TankWhite(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y), //coordinate centr
		sf::Vector2f(60, 84), //offset
		"Data/Unit/Tank3.png", //texture
		5,		//max life level
		200,	//speed move
		0,		//freeze time
		100,	//rotation speed
		sf::Vector2f(0, 77),	//create point shot
		1,		//shot life
		300,	//speed shot
		400,	//shot distance
		500,	//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
}

MovebleObject* TankWhite::Shot() { return new Bullet(1, this); }


TankBlack::TankBlack(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y), //coordinate centr
		sf::Vector2f(60, 76), //offset
		"Data/Unit/Tank4.png", //texture
		5,		//max life level
		300,	//speed move
		0,		//freeze time
		200,	//rotation speed
		sf::Vector2f(0, 68),	//create point shot
		1,		//shot life
		500,	//speed shot
		100,	//shot distance
		100,	//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
}

MovebleObject* TankBlack::Shot() { return new Bullet(1, this); }


TankYellow::TankYellow(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y), //coordinate centr
		sf::Vector2f(60, 130), //offset
		"Data/Unit/Tank5.png", //texture
		5,		//max life level
		200,	//speed move
		0,		//freeze time
		100,	//rotation speed
		sf::Vector2f(0, 121),	//create point shot
		1,		//shot life
		300,	//speed shot
		400,	//shot distance
		500,	//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
}

MovebleObject* TankYellow::Shot() { return new Bullet(1, this); }


TankGreen::TankGreen(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y), //coordinate centr
		sf::Vector2f(60, 88), //offset
		"Data/Unit/Tank6.png", //texture
		5,		//max life level
		100,	//speed move
		0,		//freeze time
		50,	//rotation speed
		sf::Vector2f(0, 80),	//create point shot
		10,		//shot life
		100,	//speed shot
		600,	//shot distance
		2000,	//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
}

MovebleObject* TankGreen::Shot() { return new Bullet(1, this); }