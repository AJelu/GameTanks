#include "ready_objects.h"

Bullet::Bullet(int const& id_object, GameObject* Parrent) : MovebleObject(
	id_object,
	sf::Vector2f(0, 0),						//coordinate centr
	sf::Vector2f(96, 96),					//offset
	"Data/Bullet/tank_attack.png",			//texture
	9, 3,									//frame count
	1000000,								//max life level
	500,									//speed move
	0,										//freeze time
	100,									//rotation speed
	Parrent) {
	this->AddAudioAction("Bullet_shot", "Data/Audio/explosion/bullet_shot.ogg", false, 50);
	this->AddAudioAction("Bullet_explosion", "Data/Audio/explosion/bullet_explosion.ogg");
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->ActionLife();
}

std::string Bullet::ClassName() { return "Bullet"; }

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
	this->StartPlayAnimation(3, 1, 8, 20);
}

DoubleBullet::DoubleBullet(int const& id_object, GameObject* Parrent) : MovebleObject(
	id_object,
	sf::Vector2f(0, 0),						//coordinate centr
	sf::Vector2f(96, 96),					//offset
	"Data/Bullet/tank_attack.png",			//texture
	9, 3,									//frame count
	1000000,								//max life level
	500,									//speed move
	0,										//freeze time
	100,									//rotation speed
	Parrent) {
	this->AddAudioAction("Double_Bullet_shot", "Data/Audio/explosion/bullet_shot.ogg", false, 50);
	this->AddAudioAction("Double_Bullet_explosion", "Data/Audio/explosion/bullet_explosion.ogg");
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 12));
	this->ActionLife();
}

std::string DoubleBullet::ClassName() { return "Bullet"; }

void DoubleBullet::ActionDie() {
	this->ClearAnimarionList(true);
	this->StartPlayAnimation(1, 1, 9, 40);
	this->StartAudioAction("Double_Bullet_explosion");
}

void DoubleBullet::ActionLife() {
	this->ClearAnimarionList(true);
	this->ActionMoving(0);
	this->StartAudioAction("Double_Bullet_shot");
}

void DoubleBullet::ActionMoving(float const& distance) {
	this->StartPlayAnimation(2, 1, 8, 20);
}

/* ===== TANKS ===== */
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

	this->AddAudioAction("TypedTank_move", "Data/Audio/move/tank_move.ogg", true, 50);
	this->AddAudioAction("TypedTank_rotate", "Data/Audio/move/tank_move_rotation.ogg", 
		true, 50);
	this->AddAudioAction("TypedTank_dead", "Data/Audio/explosion/tank_dead.ogg");
	this->AddAudioAction("collision", "Data/Audio/collision/collision_tank.ogg", false, 40);
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
	this->StartAudioAction("TypedTank_move");
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
	this->StartAudioAction("TypedTank_rotate");
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
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(60, 158),					//offset
		"Data/Unit/Tank1.png",					//texture
		125,									//max life level
		160,									//speed move
		0,										//freeze time
		70,										//rotation speed
		sf::Vector2f(-1,150),					//create point shot
		60,										//shot life
		300,									//speed shot
		500,									//shot distance
		700,									//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 20), 50));
	this->SetBasePoint(200); //delete
}

std::string RedTank::ClassName() { return "RedTank"; }

MovebleObject* RedTank::Shot() { 
	Bullet* bullet = new Bullet(1, this);
	bullet->SetScale(sf::Vector2f(0.88f, 0.88f));
	return bullet;
}


TankBrown::TankBrown(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(60, 137),					//offset
		"Data/Unit/Tank2.png",					//texture
		100,									//max life level
		160,									//speed move
		0,										//freeze time
		80,										//rotation speed
		sf::Vector2f(-6, 129),					//create point shot
		60,										//shot life
		400,									//speed shot
		450,									//shot distance
		700,									//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 15), 50));
}

std::string TankBrown::ClassName() { return "TankBrown"; }

MovebleObject* TankBrown::Shot() {
	Bullet* bullet = new Bullet(1, this);
	bullet->SetScale(sf::Vector2f(0.75f, 0.75f));
	return bullet;
}


TankWhite::TankWhite(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(60, 84),					//offset
		"Data/Unit/Tank3.png",					//texture
		80,										//max life level
		200,									//speed move
		0,										//freeze time
		120,									//rotation speed
		sf::Vector2f(0, 77),					//create point shot
		75,										//shot life
		300,									//speed shot
		400,									//shot distance
		700,									//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, -10), 50));
}

std::string TankWhite::ClassName() { return "TankWhite"; }

MovebleObject* TankWhite::Shot() { 
	DoubleBullet* double_bullet = new DoubleBullet(1, this);
	double_bullet->SetScale(sf::Vector2f(0.88f, 0.88f));
	return double_bullet;
}


TankBlack::TankBlack(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(60, 76),					//offset
		"Data/Unit/Tank4.png",					//texture
		70,										//max life level
		230,									//speed move
		0,										//freeze time
		140,									//rotation speed
		sf::Vector2f(0, 68),					//create point shot
		35,										//shot life
		350,									//speed shot
		400,									//shot distance
		700,									//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
}

std::string TankBlack::ClassName() { return "TankBlack"; }

MovebleObject* TankBlack::Shot() { 
	Bullet* bullet = new Bullet(1, this);
	bullet->SetScale(sf::Vector2f(0.82f, 0.82f));
	return bullet;
}


TankYellow::TankYellow(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(60, 130),					//offset
		"Data/Unit/Tank5.png",					//texture
		70,										//max life level
		220,									//speed move
		0,										//freeze time
		100,									//rotation speed
		sf::Vector2f(0, 121),					//create point shot
		50,										//shot life
		350,									//speed shot
		450,									//shot distance
		700,									//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 35), 18));
}

std::string TankYellow::ClassName() { return "TankYellow"; }

MovebleObject* TankYellow::Shot() {
	Bullet* bullet = new Bullet(1, this);
	bullet->SetScale(sf::Vector2f(0.92f, 0.92f));
	return bullet;
}


TankGreen::TankGreen(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(60, 88),					//offset
		"Data/Unit/Tank6.png",					//texture
		145,									//max life level
		140,									//speed move
		0,										//freeze time
		60,										//rotation speed
		sf::Vector2f(0, 80),					//create point shot
		90,										//shot life
		280,									//speed shot
		350,									//shot distance
		700,									//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 48));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 15), 48));
}

std::string TankGreen::ClassName() { return "TankGreen"; }

MovebleObject* TankGreen::Shot() { return new Bullet(1, this); }